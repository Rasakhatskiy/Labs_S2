#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include "..\Include\Message.hpp"


class DataBase
{
public:
    std::vector<Message> MemoryBase;

    DataBase();
    ~DataBase();

    void PrintFromMemory();
    void AddMessage(Message message);
};

#endif //DATABASE_HPP



