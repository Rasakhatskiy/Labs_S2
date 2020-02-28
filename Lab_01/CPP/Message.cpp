#include "..\Include\Message.hpp"

Message::Message()
{
	ID = -1;
}

Message::Message(
        unsigned int id,
        std::string text,
        DateTime time,
        std::string author,
        std::string recipient,
        Message::MessageType type, 
        float rate)
{
    ID = id;
    Text = text;
    Time = time;
    Author = author;
    Recipient = recipient;
    Type = type;
    Rate = rate;
}

int Message::GetSize()
{
	int size = sizeof(this);
	size += Author.size();
	size += Recipient.size();
	size += Text.size();
	return size;
}
