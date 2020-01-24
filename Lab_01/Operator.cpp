#include "Operator.h"


void Operator::Add()
{
    Message message = Message();
    message.Text = ReadStringMultiLine();
    //todo time
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
        std::cout << "\t>";
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
        std::cout << "\t>";
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
        std::cout << "\t>";
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
        std::cout << "\t>";
        std::cin >> result;
        valid = result >= 0;
        if (!valid) std::cout << "YOU ARE WRONG! TRY AGAIN!" << std::endl;
    } while (!valid);
    return result;
}

time_t Operator::ReadDateTime()
{
    std::cout << "Enter date and time in yyyy:mm:dd HH:mm:ss format" << std::endl;
    std::string result;
    time_t time = time_t();
    
    bool valid = false;
    int c = 0;

    //year
    while (c < 4)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    std::cout << '-';
    result += '-';
    c = 0;

    //month
    while (c < 2)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    std::cout << '-';
    result += '-';
    c = 0;

    //day
    while (c < 2)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    std::cout << ' ';
    result += ' ';
    c = 0;

    //hour
    while (c < 2)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    std::cout << ':';
    result += ':';
    c = 0;

    //minute
    while (c < 2)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    std::cout << ':';
    result += ':';
    c = 0;

    //second
    while (c < 2)
    {
        char key = (char)_getch();
        if (isdigit(c)) { result += key; c++; }
        else std::cout << "\b";
    }
    
    struct tm tm;
    //_strptime(result, "%Y-%m-%d %H:%M:%S", &tm);
    time_t t = mktime(&tm);
   

    return t;//todo;
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
