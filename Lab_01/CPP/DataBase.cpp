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

        if (file.eof()) break;

        file.read(author, sizeAuthor);
        file.read(recipient, sizeRecipient);
        file.read(text, sizeText);

        author[sizeAuthor] = '\0';
        recipient[sizeRecipient] = '\0';
        text[sizeText] = '\0';


        MemoryBase.push_back(Message::Message(
            id, 
            std::string(text), 
            DateTime::DateTime(time), 
            std::string(author), 
            std::string(recipient), 
            Message::GetType((char)typeB), 
            rate));

        delete[] author, recipient, text;
    }
    file.close();
    return 0;
}

int DataBase::ReadText()
{
	if (!FileExists(PathText))
		return -1;

	MemoryBase.clear();

	std::ifstream file;
	file.open(PathText, std::ios::in);

	std::string lineInfo;
	std::string lineAuthor;
	std::string lineRecipient;
	std::string lineType;
	std::string lineMessage;
	std::string lineRate;
	std::string message;


	while (!file.eof())
	{
		int error = 0;
		bool endMessage = false;

		unsigned id;
		DateTime dateTime;
		std::string author;
		std::string recipient;
		Message::MessageType type;
		float rate;

		std::getline(file, lineInfo);
		if (file.eof())break;
		if (lineInfo[0] != '-') return ERROR::FileCorrupted;
		error = ReadIdDate(lineInfo, id, dateTime);
		if (error != 0) return error;

		std::getline(file, lineAuthor);
		if (lineAuthor[2] != '>') return ERROR::FileCorrupted;
		author = lineAuthor.substr(13, lineAuthor.size() - 1);

		std::getline(file, lineRecipient);
		if (lineRecipient[1] != '<') return ERROR::FileCorrupted;
		recipient = lineRecipient.substr(16, lineRecipient.size() - 1);

		std::getline(file, lineType);
		if (lineType[3] != '[') return ERROR::FileCorrupted;
		type = Message::GetType(lineType[4]);

		do 
		{
			std::getline(file, lineMessage);
			if (lineMessage.size() > 15)
			{
				if (lineMessage.substr(3, 11) == "Spam rate :")
				{
					lineRate = lineMessage.substr(14, lineMessage.size() - 1);
					endMessage = true;
				}
			}
			if (!endMessage) message += lineMessage + "\n";

			if(file.eof() && !endMessage) return ERROR::FileCorrupted;
		} while (!endMessage);
		rate = std::stod(lineRate);
		
		MemoryBase.push_back(Message(
			id,
			message,
			dateTime,
			author,
			recipient,
			type,
			rate));
	}
	return 0;
}


int DataBase::SaveMemoryToBin()
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

int DataBase::SaveMemoryToText()
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


int DataBase::AppendToBin(Message message)
{

	/*MaxID = 0;*/
	//MaxElements = 0;

	int readRes = ReadIDs();

    std::ofstream file;
    uint32_t number;

    file.open(PathBin, std::ios::out | std::ios::app | std::ofstream::binary);

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    uint32_t id = ++MaxID;
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


void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
}


int DataBase::SearchByText(std::string fragment)
{
	ReadBin();
	std::vector<Message> result;
	for (auto& i : MemoryBase)
	{
		if (i.Text.find(fragment) != std::string::npos)
		{
			result.push_back(i);
		}
	}
	MemoryBase = result;
	return 0;
}

int DataBase::SearchRateAuthor(std::string author, float rateMin, float rateMax)
{
	ReadBin();
	std::vector<Message> result;
	std::transform(
		author.begin(), 
		author.end(), 
		author.begin(),
		[](unsigned char c) { return std::tolower(c); });

	for (auto& i : MemoryBase)
	{
		std::string a = i.Author;
		std::transform(
			a.begin(),
			a.end(),
			a.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (a == author && i.Rate >= rateMin && i.Rate <= rateMax)
		{
			result.push_back(i);
		}
	}
	MemoryBase = result;
	return 0;
}

int DataBase::SearchTypeTime(Message::MessageType type, DateTime dateTimeBefore)
{
	ReadBin();
	std::vector<Message> result;
	for (auto& i : MemoryBase)
	{
		if (i.Type == type && i.Time < dateTimeBefore)
		{
			result.push_back(i);
		}
	}
	MemoryBase = result;
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

	while (!file.eof())
	{
		file.read(reinterpret_cast<char*>(&id), sizeof(id));
		file.ignore(sizeof(int));
		file.ignore(sizeof(float));
		file.ignore(sizeof(Byte));
		file.read(reinterpret_cast<char*>(&sizeAuthor), sizeof(sizeAuthor));
		file.read(reinterpret_cast<char*>(&sizeRecipient), sizeof(sizeRecipient));
		file.read(reinterpret_cast<char*>(&sizeText), sizeof(sizeText));
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

int DataBase::ReadIdDate(std::string source, unsigned& id, DateTime& datetime)
{
	bool readId = false;
	bool toReadId = false;
	bool toReadDate = false;
	std::string idStr, dateString;

	try
	{
		for (auto& i : source)
		{
			if (i == '[')
			{
				if (!readId)
					toReadId = true;
				else
					toReadDate = true;
				continue;
			}

			if (i == ']')
			{
				if (toReadId)
				{
					toReadId = false;
					readId = true;
				}

				if (toReadDate)
					break;

				continue;
			}
			if (toReadId) idStr += i;
			if (toReadDate) dateString += i;
		}

		id = std::stoi(idStr);
		datetime = DateTime(dateString);
	}
	catch (...)
	{
		return ERROR::FileCorrupted;
	}
	return 0;
}
