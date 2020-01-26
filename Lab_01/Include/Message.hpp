#ifndef LAB_1_MESSAGE_HPP
#define LAB_1_MESSAGE_HPP

#include <string>
#include <ctime>
#include "..\Include\DateTime.hpp"

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
    float Rate;

    Message();

    Message(unsigned int id,
            std::string text,
            DateTime time,
            std::string author,
            std::string recipient,
            MessageType type, 
            float rate);


};

#endif //LAB_1_MESSAGE_HPP
