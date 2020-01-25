#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Message.h"


class DataBase
{
public:
    std::vector<Message> MemoryBase;

    DataBase();
    ~DataBase();

    void PrintFromMemory();
    void AddMessage(Message message);
};

#endif //DATABASE_H



