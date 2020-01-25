#include "..\Include\DataBase.hpp"



DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}


void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
}
