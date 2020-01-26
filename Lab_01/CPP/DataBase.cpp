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

int DataBase::LoadFromBin()
{
    bool successRead = false;
    
    return 0;
}

int DataBase::ReadBin()
{
    /*if (!FileExists(PathBin))
        return -1;*/

    std::ifstream file;
    file.open(PathBin, std::ios::in | std::ios::binary);

    uint32_t number;
    file.read(reinterpret_cast<char *>(&number), sizeof(number));

    uint32_t check;
    file.read(reinterpret_cast<char *>(&check), sizeof(check));
    if (check != 0xFFFFFFFF) return -2;

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]
    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;
    uint32_t id, sizeAuthor, sizeRecipient, sizeText;

    for (int i = 0; i < number; ++i)
    {
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        if (id > largestId) largestId = id;
        file.ignore(5);
        file.read(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
        file.read(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
        file.read(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));
        file.ignore(sizeAuthor + sizeRecipient + sizeText);
        
    }
    file.read(reinterpret_cast<char *>(&check), sizeof(check));
    if (check != 0xFFFFFFFF) return -2;
    MaxID = largestId;
    file.close();
    return 0;
}

int DataBase::SaveToBin()
{
    //if (ReadBin != 0) 
    MaxID = 0;
    std::ofstream file;

    file.open(PathBin, std::ios::out | std::ios::binary);
        
    /*if (MaxID == 0)
    {

    }*/
    uint32_t number = MemoryBase.size();
    file.write(reinterpret_cast<char *>(&number), sizeof(number));

    uint32_t check = 0xFFFFFFFF;
    file.write(reinterpret_cast<char *>(&check), sizeof(check));

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]
    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    for (int i = 0; i < number; ++i)
    {
        uint32_t id = i;
        uint32_t time = MemoryBase[i].Time.Time;
        float rate = MemoryBase[i].Rate;
        uint8_t type = MemoryBase[i].Type;
        uint8_t sizeAuthor = MemoryBase[i].Author.size();
        uint8_t sizeRecipient = MemoryBase[i].Recipient.size();
        uint32_t sizeText = MemoryBase[i].Text.size();

        file.write(reinterpret_cast<char *>(&id), sizeof(id));
        file.write(reinterpret_cast<char *>(&time), sizeof(time));
        file.write(reinterpret_cast<char *>(&rate), sizeof(rate));
        file.write(reinterpret_cast<char *>(&type), sizeof(type));
        file.write(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
        file.write(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
        file.write(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));

        file << MemoryBase[i].Author;
        file << MemoryBase[i].Recipient;
        file << MemoryBase[i].Text;
    }
    file.write(reinterpret_cast<char *>(&check), sizeof(check));
    file.close();
    return 0;
}


void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
}

inline bool FileExists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}