#include "DataBase.h"



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
