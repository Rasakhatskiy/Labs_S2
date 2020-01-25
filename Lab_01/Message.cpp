#include "Message.h"

Message::Message()
{
}

Message::Message(
        unsigned int id,
        std::string text,
        DateTime time,
        std::string author,
        std::string recipient,
        Message::MessageType type, double rate)
{
    ID = id;
    Text = text;
    Time = time;
    Author = author;
    Recipient = recipient;
    Type = type;
    Rate = rate;
}
