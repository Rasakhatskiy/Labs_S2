#ifndef OPERATOR_H
#define OPERATOR_H
#include "Message.h"
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
    time_t ReadDateTime();

    bool IsValidStringName(std::string name);

    Operator();
    ~Operator();
};

#endif //OPERATOR_H
