#include "..\Include\DataBase.hpp"



DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}

int DataBase::SaveToText()
{
    std::ofstream textFile;
    textFile.open(PathText);

    for (int id = 0; id < MemoryBase.size(); id++)
    {
        auto message = MemoryBase[id];
        textFile << "-----Message [" << id << "][" << message.Time.ToString() << "]-----\n";
        textFile << " -> Author : " + message.Author + "\n";
        textFile << " <- Recipient : " + message.Recipient + "\n";
        std::string type;
        switch (message.Type)
        {
            case Message::MessageType::Answer: type = "Answer"; break;
            case Message::MessageType::Comment: type = "Comment"; break;
            case Message::MessageType::Invite: type = "Invite"; break;
            case Message::MessageType::News: type = "News"; break;
            case Message::MessageType::Question: type = "Question"; break;
            default:type = "Nuclear Missile Launch Codes";
        }
        textFile << "   [" + type + "]\n";
        textFile << message.Text;
        textFile << "\n   Spam rate : " << message.Rate << std::endl;
    }
    textFile.close();
    return 0;
}

int DataBase::SaveToBin()
{
    return 0;
}


void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
}
