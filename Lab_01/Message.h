#ifndef LAB_1_MESSAGE_H
#define LAB_1_MESSAGE_H

#include <string>
#include <ctime>
#include "DateTime.h"

class Message
{
public:
    enum MessageType
    {
        News,
        Question,
        Answer,
        Invite,
        Comment
    };

    unsigned int ID;
    std::string Text;
    DateTime Time;
    std::string Author;
    std::string Recipient;
    MessageType Type;
    double Rate;

    Message();

    Message(unsigned int id,
            std::string text,
            DateTime time,
            std::string author,
            std::string recipient,
            MessageType type, 
            double rate);
};

#endif //LAB_1_MESSAGE_H
