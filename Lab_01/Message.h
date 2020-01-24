#ifndef LAB_1_MESSAGE_H
#define LAB_1_MESSAGE_H

#include <string>
#include <ctime>

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
    std::time_t Time;
    std::string Author;
    std::string Recipient;
    MessageType Type;
    double Rate;

    Message();

    Message(unsigned int id,
            std::string text,
            std::time_t time,
            std::string author,
            std::string recipient,
            MessageType type, 
            double rate);
};

#endif //LAB_1_MESSAGE_H
