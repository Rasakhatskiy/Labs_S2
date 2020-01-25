#ifndef OPERATOR_HPP
#define OPERATOR_HPP
#include "..\Include\Message.hpp"
#include "..\Include\DateTime.hpp"
#include "..\Include\DataBase.hpp"
#include <vector>
#include <iostream>
#include <conio.h>
#include <ctime>

class Operator
{
private:
    DataBase _DataBase;

    Message ReadMessage();

    std::string ReadStringMultiLine();
    std::string ReadStringShort();

    Message::MessageType ReadMessageType();

    DateTime ReadDateTime();

    double ReadDouble();
    void PrintMessage(int id, Message message);
    bool IsValidStringName(std::string name);

public:
    void Add();
    void PrintMemory();
    Operator();
    ~Operator();
};

#endif //OPERATOR_HPP