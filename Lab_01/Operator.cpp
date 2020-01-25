#include "Operator.h"

void Operator::Add()
{
    Message message = Message();
    message.Text = ReadStringMultiLine();
    message.Time = ReadDateTime();
    message.Author = ReadStringShort();
    message.Recipient = ReadStringShort();
    message.Type = ReadMessageType();
    message.Rate = ReadDouble();
}

std::string Operator::ReadStringMultiLine()
{
    std::cout << "Enter text message. To stop write :wq from a new line;" << std::endl;
    std::string buffer, result;
    const std::string cancel = ":wq";
    do
    {
        std::cout << ">";
        result += buffer + "\n";
    }
    while (std::getline(std::cin, buffer) && buffer != cancel);
    return result;
}

std::string Operator::ReadStringShort()
{
    std::cout << "Enter text value no longer than 255 symbols. Allowed symbols A-Z a-z 0-9" << std::endl;
    std::string result;
    bool valid = false;
    do
    {
        std::cout << ">";
        std::cin >> result;
        valid = IsValidStringName(result);
        if (!valid) std::cout << "YOU ARE WRONG! TRY AGAIN!" << std::endl;

    } while (!valid);
    return result;
}

Message::MessageType Operator::ReadMessageType()
{
    std::cout << "Enter message type ([N]ews, [Q]uestion, [A]nswer, [I]nvite, [C]omment" << std::endl;
    bool valid = false;
    std::string allowed = "NnQqAaIiCc";
    std::string result;
    do
    {
        std::cout << ">";
        std::cin >> result;
        for (const char c : allowed)
        {
            if (result[0] == c)
            {
                valid = true;
                break;
            }
        }
        if (!valid) std::cout << "YOU ARE WRONG! TRY AGAIN!" << std::endl;
    } while (!valid);
    char c = tolower(result[0]);
    switch (c)
    {
        case 'n': return Message::MessageType::News;
        case 'q': return Message::MessageType::Question;
        case 'a': return Message::MessageType::Answer;
        case 'i': return Message::MessageType::Invite;
        case 'c': return Message::MessageType::Comment;
    }
}

double Operator::ReadDouble()
{
    std::cout << "Enter message spam rate higher than 0" << std::endl;
    bool valid = false;
    double result;
    do
    {
        std::cout << ">";
        std::cin >> result;
        valid = result >= 0;
        if (!valid) std::cout << "YOU ARE WRONG! TRY AGAIN!" << std::endl;
    } while (!valid);
    return result;
}

DateTime Operator::ReadDateTime()
{
    std::cout << "Enter date and time in yyyy-mm-dd HH:mm:ss format" << std::endl;
    std::cout << ">";
    std::string str;
    bool valid = false;
    int c = 0;
    char key;

    while (c < 19)
    {
        if (c == 4 || c == 7) 
        {
            str += '-';
            std::cout << '-';
            c++;
            continue;
        }
        if (c == 10)
        {
            str += ' ';
            std::cout << ' ';
            c++;
            continue;
        }
        if (c == 13 || c == 16)
        {
            str += ':';
            std::cout << ':';
            c++;
            continue;
        }
        key = (char)_getch();
        if (isdigit(key))
        {
            str += key;
            c++;
            std::cout << key;
        }
    }
    std::cout << std::endl;

    return DateTime(
        std::stoi(str.substr(0, 4)),
        std::stoi(str.substr(5, 2)),
        std::stoi(str.substr(8, 2)),
        std::stoi(str.substr(11, 2)),
        std::stoi(str.substr(14, 2)),
        std::stoi(str.substr(17, 2)));
}

bool Operator::IsValidStringName(std::string name)
{
    for (const char c : name) 
        if (!isalpha(c) && !isdigit(c))
            return false;

    return true;
}




Operator::Operator()
{
    
}

Operator::~Operator()
{
}
