#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include <map>

struct Type_info
{
    int32_t left_buff_size; // size for msg, left in buffer
    int32_t msg_count; // number of msg of the type

    Type_info();
    void init_msg();
};

Type_info::Type_info(): left_buff_size(2048), msg_count(1) {}


//void binary_reader( std::string file_name, std::vector<Message*>&msg_vector);
void binary_reader( std::string file_name, std::map<size_t, Type_info*>&msg_map);

int max_time = 0;
int min_time = 0;

int main()
{
    std::map<size_t, Type_info*> msg_map;

    std::string str = ("input.txt");

    binary_reader(str, msg_map);


    //count time period
    double diff_time = max_time - min_time + 1;
    //member for saving average namber of messagies during the whole period og time
    double average = 0;
    std::map<size_t, Type_info*>::iterator it;
    std::ofstream of("output.txt", std::ios::binary);
    if(of)
    {
        for(it = msg_map.begin(); it != msg_map.end(); it++)
        {
            average = (double)((*it).second->msg_count/(diff_time));
            of.write((char*)&(*it).first, sizeof(int32_t));
            of.write((char*)&average , sizeof(double));
        }
    }

    //clean the map
    for(it = msg_map.begin(); it != msg_map.end(); ++it)
        delete it->second;
    msg_map.clear();

    of.close();
    return 0;
}

void binary_reader( std::string file_name, std::map<size_t, Type_info*>&msg_map)
{
    std::ifstream in(file_name, std::ios::binary);
    if(in)
    {
        //get length of file
        in.seekg(0, in.end);
        int length = in.tellg();
        in.seekg(0, in.beg);

        //we don't need the message itself for our statistics
        //so we can just save the pos in order to know the pos wor reading the info
        //on the next step
        size_t pos = 0;
        size_t type = 0;
        size_t msg_len = 0;
        int32_t tmp = 0;
        int32_t cur_time = 0;

        //a flag to fix the min_time
        int flag = 0;
        Type_info* msg = NULL;
        std::map<size_t, Type_info*>::iterator it;
        while(length > 0)
        {
            msg = new Type_info();
            in.read((char*)&type, sizeof(int32_t));
            in.read((char*)&cur_time, sizeof(int32_t));
            if(flag == 0)
            {
                min_time = cur_time;
                ++flag;
            }
            if(cur_time > max_time)
                max_time = cur_time;
            in.read((char*)&msg_len, sizeof(int32_t));
            tmp = (msg_len + 3*sizeof(int32_t));
            //chack if type is already in map and 
            //if it is - check its params
            it = msg_map.find(type);
            if(it != msg_map.end() && ((*it).second)->left_buff_size > tmp)
            {
                ((*it).second)->left_buff_size -= tmp;
                ((*it).second)->msg_count++;
                delete msg;
            }
            else
                msg_map.insert(std::pair<size_t, Type_info*>(type, msg));
            it = msg_map.find(type);
            length -= tmp;
            pos += tmp;
            in.seekg(pos);
        }
    }
    else
        std::cout << "problemes with input.txt" << std::endl;
    in.close();
}
