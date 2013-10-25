#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint> //for int32_t


struct Message
{
    int32_t m_type;
    int32_t m_time; // time since start
    int32_t m_len;
    char* m_msg = NULL;

    Message();
    Message(int32_t, int32_t, int32_t);
    ~Message();
    void init_msg();
};

Message::Message():m_type(0),m_time(0),m_len(0),m_msg(NULL){}

Message::Message(int32_t type, int32_t time, int32_t len)
{
    if(type, len, time)
    {
        m_type = type;
        m_time = time;
        m_len = len;
        m_msg = new char[m_len];
    }

}

void Message::init_msg()
{
    if(m_len && !m_msg)
        m_msg = new char[m_len];
}

Message::~Message()
{
    if(m_msg)
        delete[] m_msg;
}

void binary_reader(std::string file_name, std::vector<Message*>&msg_vector, int32_t& curr_time);

int main()
{

    int32_t type, time, len;
    int32_t current_time = 0; //max of times from file

    std::vector<Message*> msg_vector;

    //let's read data from file
    std::string str =  ("2.4_example.in");
    binary_reader( str, msg_vector, current_time);

    std::cout << "current: " << current_time << std::endl;
    //filter files: 1) m_time > current_time-2
    //              2) only msg of types, defined in Type
    // std::ofstream os("output.txt" );
    std::ofstream of("output.out", std::ios::binary);
    if(of)
    {
        std::vector<Message*>::iterator end = msg_vector.end();
        for(std::vector<Message*>::iterator it = msg_vector.begin(); it != end; it++)
        {
            //as types [1;4] were defined in conditions I've hard-coded a little
            if((int32_t)(*it)->m_type <= (int32_t)4 &&  (int32_t)(*it)->m_time > (current_time-2))
            {
                of.write((char*)&(*it)->m_type, sizeof(int32_t));
                of.write((char*)&(*it)->m_time, sizeof(int32_t));
                of.write((char*)&(*it)->m_len, sizeof(int32_t));
                of.write((char*)(*it)->m_msg, (*it)->m_len);
                //std::cout << "Message: " << (*it)->m_type << " " << (*it)->m_time << " " << (*it)->m_len << " " << (char*)(*it)->m_msg << std::endl;
            }
        }
    }
    else
        std::cout << "Problemes with output file" << std::endl;

    of.close();

    std::vector<Message*>::iterator end = msg_vector.end();
    for(std::vector<Message*>::iterator it = msg_vector.begin(); it != end; it++)
        delete *it;

    return 0;
}

void binary_reader( std::string file_name, std::vector<Message*>&msg_vector, int32_t& curr_time)
{
    // read data from file
    std::ifstream in(file_name, std::ios::binary);
    if(in)
    {
        // get length of file:
        in.seekg (0, in.end);
        int length = in.tellg();
        in.seekg (0, in.beg);

        Message* msg = NULL;
        //read data, form a struct and push it back to msg-vector
        while(length > 0)
        {
            msg = new Message();
            in.read((char*)&(msg->m_type), sizeof(int32_t));
            in.read((char*)&(msg->m_time), sizeof(int32_t));
            if(curr_time < msg->m_time)
                curr_time = msg->m_time;
            in.read((char*)&(msg->m_len), sizeof(int32_t));
            if(msg->m_len)
            {
                msg->init_msg();
                in.read(msg->m_msg, msg->m_len);
                length -= (3*sizeof(int32_t)+(msg->m_len));
                //std::cout << "msg: " << msg.m_type << " " << msg.m_time << " " << msg.m_len << " " << msg.m_msg << std::endl;
                msg_vector.push_back(msg);
            }
        }
    }
    else
        std::cout << "problemes with input.txt" << std::endl;
    in.close();

}
