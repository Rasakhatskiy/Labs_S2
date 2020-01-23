#include "Message.h"

Message::Message(
        std::string text,
        std::time_t time,
        std::string author,
        std::string recipient,
        Message::MessageType type,
        double rate)
{
    Text = text;
    Time = time;
    Author = author;
    Recipient = recipient;
    Type = type;
    Rate = rate;
}
