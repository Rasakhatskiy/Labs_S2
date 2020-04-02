#ifndef LAB_1_MESSAGE_HPP
#define LAB_1_MESSAGE_HPP

#include <string>
#include <ctime>
#include "..\Include\DateTime.hpp"
#define Byte unsigned char

class Message
{
public:
    enum MessageType
    {
		Answer,
		Comment,
		Invite,
        News,
        Question
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

	int GetSize();

    static MessageType GetType(char ch)
    {
        ch = tolower(ch);
        switch (ch)
        {
            case 'n': return Message::MessageType::News;
            case 'q': return Message::MessageType::Question;
            case 'a': return Message::MessageType::Answer;
            case 'i': return Message::MessageType::Invite;
            case 'c': return Message::MessageType::Comment;
        }
		return Message::MessageType::Comment; //just because
    }
};

#endif //LAB_1_MESSAGE_HPP
