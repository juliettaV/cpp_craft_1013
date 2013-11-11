#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cstdint>
#include <stdlib.h>

struct Message
{
    char* stock_name = NULL;
    char* date_time = NULL;
    double price;
    double vwap;
    int32_t volume;
    double f1, t1, f2, f3, f4;

    Message();
    ~Message();
};

Message::Message():price(0),vwap(0),volume(0),f1(0), f2(0), f3(0), f4(0),t1(0)
{
    if(!stock_name)
        stock_name = new char[9];
    if(!date_time)
        date_time = new char[8];
}

Message::~Message()
{
    if(stock_name)
        delete[] stock_name;
    if(date_time)
        delete[] date_time;
}
void binary_reader( std::string file_name, std::vector<Message*>&msg_vector);

int main()
{
    std::vector<Message*> msg_vector;
    std::string file_name = ("input.txt");

    //Read the info from input file
    binary_reader(file_name, msg_vector);

    //write down the info to output file
    int days = 0;
    int months_days = 0;
    int year_days = 0;
    int date = 0;
    std::ofstream of("output.txt", std::ios::binary);
    if(of)
    {
        std::vector<Message*>::iterator end = msg_vector.end();
        for(std::vector<Message*>::iterator it = msg_vector.begin(); it != end; it++)
        {
            of.write((char*)&(*it)->stock_name, sizeof(8));
            //transform from YYYYMMDD to days
            days = atoi((*it)->date_time)%100;
            months_days =  ((atoi((*it)->date_time)%10000 - days)/100-1)*31;
            year_days = ((atoi((*it)->date_time)%100000000 - months_days)/10000-1)*372;
            date = days+months_days+year_days;

            //write info to file
            of.write((char*)&date, sizeof(date));
            of.write((char*)&(*it)->vwap, sizeof(int32_t));
            of.write((char*)&(*it)->volume, sizeof(int32_t));
            of.write((char*)&(*it)->f2, sizeof(double));
        }
    }

    //delete and clean vector of Messages
    std::vector<Message*>::iterator end = msg_vector.end();
    for(std::vector<Message*>::iterator it = msg_vector.begin(); it != end; it++)
        delete *it;

    return 0;
}

void binary_reader( std::string file_name, std::vector<Message*>&msg_vector)
{
    std::ifstream in(file_name, std::ios::binary);
    if(in)
    {
        //get length of file
        in.seekg(0, in.end);
        int length = in.tellg();
        in.seekg(0, in.beg);

        Message* msg = NULL;
        //read data, form a struct and push it back to msg-vector
        while(length > 0)
        {
            msg = new Message();
            in.read((char*)(msg->stock_name), 9);
            in.read((char*)(msg->date_time), 8);
            in.read((char*)&(msg->price), sizeof(double));
            in.read((char*)&(msg->vwap), sizeof(double));
            in.read((char*)&(msg->volume), sizeof(int32_t));
            in.read((char*)&(msg->f1), sizeof(double));
            in.read((char*)&(msg->t1), sizeof(double));
            in.read((char*)&(msg->f2), sizeof(double));
            in.read((char*)&(msg->f3), sizeof(double));
            in.read((char*)&(msg->f4), sizeof(double));
            msg_vector.push_back(msg);
            length-= (16+7*sizeof(double)+sizeof(int32_t));
        }
    }
    else
        std::cout << "problemes with input.txt" << std::endl;
    in.close();
}
