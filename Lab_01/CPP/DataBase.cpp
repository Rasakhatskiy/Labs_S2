#include "..\Include\DataBase.hpp"
inline bool FileExists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

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


int DataBase::ReadBin()
{
    if (!FileExists(PathBin))
        return -1;

    MemoryBase.clear();

    std::ifstream file;
    file.open(PathBin, std::ios::in | std::ios::binary);

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]

    uint32_t id, time, sizeText;
    float rate;
    Byte typeB, sizeAuthor, sizeRecipient;
    

    while (!file.eof())
    {
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        file.read(reinterpret_cast<char *>(&time), sizeof(time));
        file.read(reinterpret_cast<char *>(&rate), sizeof(rate));
        file.read(reinterpret_cast<char *>(&typeB), sizeof(typeB));
        file.read(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
        file.read(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
        file.read(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));

        char * author = new char[sizeAuthor + 1];
        char * recipient = new char[sizeRecipient + 1];
        char * text = new char[sizeText + 1];

        file.read(author, sizeAuthor);
        file.read(recipient, sizeRecipient);
        file.read(text, sizeText);

        author[sizeAuthor] = '\0';
        recipient[sizeRecipient] = '\0';
        text[sizeText] = '\0';

        if (file.eof()) break;

        MemoryBase.push_back(Message::Message(
            id, 
            std::string(text), 
            DateTime::DateTime(time), 
            std::string(author), 
            std::string(recipient), 
            Message::GetType((char)typeB), 
            rate));

        delete author, recipient, text;
    }
    file.close();
    return 0;
}

int DataBase::SaveToBin()
{
    MaxID = 0;
    MaxElements = 0;

    int readRes = ReadIDs();

    std::ofstream file;

    file.open(PathBin, std::ios::out | std::ios::app | std::ios::binary);

    uint32_t number = MemoryBase.size();
    if (MaxID == 0) file.write(reinterpret_cast<char *>(&number), sizeof(number));

    uint32_t check = I_LOVE_KNU_EXCEPT_MATAN;
    if(MaxID == 0) file.write(reinterpret_cast<char *>(&check), sizeof(check));

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    for (int i = 0; i < number; ++i)
    {
        uint32_t id = MaxID++;
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
        MaxElements++;
    }
    file.seekp(0);

    number = MaxElements;
    if (MaxID == 0) file.write(reinterpret_cast<char *>(&number), sizeof(number));
    file.close();
    return 0;
}

int DataBase::SaveToBin(Message message)
{
    std::ofstream file;
    uint32_t number;

    file.open(PathBin, std::ios::out | std::ios::app | std::ofstream::binary);

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    uint32_t id = MaxID++;
    uint32_t time = message.Time.Time;
    float rate = message.Rate;
    uint8_t type = message.Type;
    uint8_t sizeAuthor = message.Author.size();
    uint8_t sizeRecipient = message.Recipient.size();
    uint32_t sizeText = message.Text.size();

    file.write(reinterpret_cast<char *>(&id), sizeof(id));
    file.write(reinterpret_cast<char *>(&time), sizeof(time));
    file.write(reinterpret_cast<char *>(&rate), sizeof(rate));
    file.write(reinterpret_cast<char *>(&type), sizeof(type));
    file.write(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
    file.write(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
    file.write(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));

    file.write(message.Author.c_str(), message.Author.size());
    file.write(message.Recipient.c_str(), message.Recipient.size());
    file.write(message.Text.c_str(), message.Text.size());
    MaxElements++;

    file.close();
    return 0;
}

int DataBase::ReadIDs() 
{
    if (!FileExists(PathBin))
    {
        MaxElements = 0;
        MaxID = 0;
        return -1;
    }

    std::vector<int> newIDs;

    std::ifstream file;
    file.open(PathBin, std::ios::in | std::ios::binary);

   /* uint32_t number;
    file.read(reinterpret_cast<char *>(&number), sizeof(number));

    uint32_t check;
    file.read(reinterpret_cast<char *>(&check), sizeof(check));
    if (check != I_LOVE_KNU_EXCEPT_MATAN) return -2;*/

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]

    uint32_t id, sizeText;
    Byte sizeAuthor, sizeRecipient;

    while(!file.eof())
    {
        file.read(reinterpret_cast<char *>(&id), sizeof(id));
        file.ignore(sizeof(int));
        file.ignore(sizeof(float));
        file.ignore(sizeof(Byte));
        file.read(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
        file.read(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
        file.read(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));
        file.ignore(sizeAuthor);
        file.ignore(sizeRecipient);
        file.ignore(sizeText);
        newIDs.push_back(id);
    }

    file.close();

    IDs.clear();
    IDs = newIDs;

    MaxID = 0;
    MaxElements = IDs.size();
    for (int i = 0; i < IDs.size(); i++)
        if (IDs[i] > MaxID) MaxID = IDs[i];

    return 0;
}

void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
}