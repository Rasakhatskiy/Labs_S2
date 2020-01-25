#ifndef OPERATOR_H
#define OPERATOR_H
#include "Message.h"
#include "DateTime.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <ctime>

class Operator
{
    std::vector<Message> MemoryStorage;
public:
    void Add();
    std::string ReadStringMultiLine();
    std::string ReadStringShort();
    Message::MessageType ReadMessageType();
    double ReadDouble();
    DateTime ReadDateTime();

    bool IsValidStringName(std::string name);

    Operator();
    ~Operator();
};

#endif //OPERATOR_H
