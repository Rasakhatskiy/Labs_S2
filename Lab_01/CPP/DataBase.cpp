#include "..\Include\DataBase.hpp"

DataBase::DataBase()
{
}
DataBase::~DataBase()
{
}


int DataBase::ReadIDsBin()
{
	if (!FileExists(PathBin))
	{
		MaxElements = 0;
		MaxID_BIN = 0;
		return ERROR::FileDoesntExists;
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

	MaxID_BIN = 0;
	MaxElements = IDs.size();
	for (int i = 0; i < IDs.size(); i++)
		if (IDs[i] > MaxID_BIN) MaxID_BIN = IDs[i];

	return 0;
}

int DataBase::ReadIDsText() 
{
	int error = ReadText();
	if (error != 0)
		return error;

	MaxID_TXT = 0;
	for(auto &i : MemoryBase)
	{
		if (i.ID > MaxID_TXT) MaxID_TXT = i.ID;
	}
}


int DataBase::ReadBin(int searchId)
{
	if (!FileExists(PathBin))
		return ERROR::FileDoesntExists;

    MemoryBase.clear();

    std::ifstream file;
    file.open(PathBin, std::ios::in | std::ios::binary);

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]

    uint32_t id, time, sizeText;
    float rate;
    Byte typeB, sizeAuthor, sizeRecipient;
    
	LastPointerBegin = -1;
	LastPointerEnd = -1;

    while (!file.eof())
    {
        file.read(reinterpret_cast<char *>(&id), sizeof(id));

		if (id == searchId) LastPointerBegin = (long)file.tellg() - 4;

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

		if (id == searchId) LastPointerEnd = file.tellg();

        author[sizeAuthor] = '\0';
        recipient[sizeRecipient] = '\0';
        text[sizeText] = '\0';


        MemoryBase.push_back(Message::Message(
            id, 
            std::string(text), 
            DateTime::DateTime(time), 
            std::string(author), 
            std::string(recipient), 
            (Message::MessageType)typeB, 
            rate));

        delete[] author, recipient, text;

		if (LastPointerBegin != -1 && LastPointerEnd != -1 && id != -1)
			break;
    }
    file.close();
    return 0;
}

int DataBase::ReadText(int searchId)
{
	if (!FileExists(PathText))
		return ERROR::FileDoesntExists;

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

	LastPointerBegin = -1;
	LastPointerEnd = -1;

	while (!file.eof())
	{
		message = "";
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

		if (id == searchId) LastPointerBegin = (long)file.tellg() - 4;

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
		
		if (id == searchId) LastPointerEnd = file.tellg();

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
    MaxID_BIN = 0;
    MaxElements = 0;

    int readRes = ReadIDsBin();

    std::ofstream file;

    file.open(PathBin, std::ios::out | std::ios::app | std::ios::binary);

    uint32_t number = MemoryBase.size();

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    for (int i = 0; i < number; ++i)
    {
        uint32_t id = MaxID_BIN++;
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
    if (MaxID_BIN == 0) file.write(reinterpret_cast<char *>(&number), sizeof(number));
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


int DataBase::AppendToBin(Message _message, int _id)
{
	int readRes = ReadIDsBin();

    std::ofstream file;
    uint32_t number;

    file.open(PathBin, std::ios::out | std::ios::app | std::ofstream::binary);

    //[ID, Time, Rate, Type, SAauthor, SRecipient, SText, Author, Recipient, Text]

    //[4b, 4b,   4b,   1b,   1b,       1b,         4b,    SA,     SR,        ST  ]
    unsigned largestId = 0;

    uint32_t id = (_id == -1) ? ++MaxID_BIN : _id;
    uint32_t time = _message.Time.Time;
    float rate = _message.Rate;
    uint8_t type = _message.Type;
    uint8_t sizeAuthor = _message.Author.size();
    uint8_t sizeRecipient = _message.Recipient.size();
    uint32_t sizeText = _message.Text.size();

    file.write(reinterpret_cast<char *>(&id), sizeof(id));
    file.write(reinterpret_cast<char *>(&time), sizeof(time));
    file.write(reinterpret_cast<char *>(&rate), sizeof(rate));
    file.write(reinterpret_cast<char *>(&type), sizeof(type));
    file.write(reinterpret_cast<char *>(&sizeAuthor), sizeof(sizeAuthor));
    file.write(reinterpret_cast<char *>(&sizeRecipient), sizeof(sizeRecipient));
    file.write(reinterpret_cast<char *>(&sizeText), sizeof(sizeText));

    file.write(_message.Author.c_str(), _message.Author.size());
    file.write(_message.Recipient.c_str(), _message.Recipient.size());
    file.write(_message.Text.c_str(), _message.Text.size());
    MaxElements++;

    file.close();
    return 0;
}

int DataBase::AppendToText(Message _message, int _id)
{
	std::ofstream textFile;
	ReadIDsText();
	textFile.open(PathText, std::ios_base::app);

	{
		int id = _id == -1 ? MaxID_TXT : _id;
		textFile << "-----Message [" << id << "][" << _message.Time.ToString() << "]-----\n";
		textFile << " -> Author : " + _message.Author + "\n";
		textFile << " <- Recipient : " + _message.Recipient + "\n";
		std::string type;
		switch (_message.Type)
		{
		case Message::MessageType::Answer: type = "Answer"; break;
		case Message::MessageType::Comment: type = "Comment"; break;
		case Message::MessageType::Invite: type = "Invite"; break;
		case Message::MessageType::News: type = "News"; break;
		case Message::MessageType::Question: type = "Question"; break;
		default:type = "Nuclear Missile Launch Codes";
		}
		textFile << "   [" + type + "]\n";
		textFile << _message.Text;
		textFile << "\n   Spam rate : " << _message.Rate << std::endl;
	}
	textFile.close();
	return 0;
}


int DataBase::ShiftDataBaseBin()
{
	if (!FileExists(PathBin))
		return ERROR::FileDoesntExists;

	if (LastPointerBegin == -1 || LastPointerEnd == -1)
		return ERROR::MessageNotFound;

	auto backupFile = PathBin + ".bk";
	const int bufferSize = 10 * 1024;
	std::ifstream ifile;
	std::ofstream ofile;
	char buffer[bufferSize];
	int toCopy;

	//get db size
	ifile.open(PathBin, std::ios::in | std::ios::binary | std::ios::ate);
	int fileSize = ifile.tellg();
	ifile.close();

	ifile.open(PathBin, std::ios::in | std::ios::binary);
	ofile.open(backupFile, std::ios::out | std::ios::binary);

	toCopy = LastPointerBegin;

	//copy part before shift
	while (toCopy >= bufferSize)
	{
		ifile.read(buffer, bufferSize);
		ofile.write(buffer, bufferSize);
		toCopy -= bufferSize;
	}
	{
		ifile.read(buffer, toCopy);
		ofile.write(buffer, toCopy);
		toCopy = 0;
	}

	ifile.seekg(LastPointerEnd);
	toCopy = fileSize - LastPointerEnd;
	while (toCopy >= bufferSize)
	{
		ifile.read(buffer, bufferSize);
		ofile.write(buffer, bufferSize);
		toCopy -= bufferSize;
	}
	{
		ifile.read(buffer, toCopy);
		ofile.write(buffer, toCopy);
		toCopy = 0;
	}

	ifile.close();
	ofile.close();
	LastPointerBegin = -1;
	LastPointerEnd = -1;

	std::remove(PathBin.c_str());

	if (std::rename(backupFile.c_str(), PathBin.c_str()) == 0)
		return 0;
	else
		return ERROR::RenamingError;
}

int DataBase::ShiftDataBaseText()
{
	if (!FileExists(PathText))
		return ERROR::FileDoesntExists;

	if (LastPointerBegin == -1 || LastPointerEnd == -1)
		return ERROR::MessageNotFound;

	auto backupFile = PathText + ".bk";
	const int bufferSize = 10 * 1024;
	std::ifstream ifile;
	std::ofstream ofile;
	char buffer[bufferSize];
	int toCopy;

	//get db size
	ifile.open(PathText, std::ios::in | std::ios::binary | std::ios::ate);
	int fileSize = ifile.tellg();
	ifile.close();

	ifile.open(PathText, std::ios::in | std::ios::binary);
	ofile.open(backupFile, std::ios::out | std::ios::binary);

	toCopy = LastPointerBegin;

	//copy part before shift
	while (toCopy >= bufferSize)
	{
		ifile.read(buffer, bufferSize);
		ofile.write(buffer, bufferSize);
		toCopy -= bufferSize;
	}
	{
		ifile.read(buffer, toCopy);
		ofile.write(buffer, toCopy);
		toCopy = 0;
	}

	ifile.seekg(LastPointerEnd);
	toCopy = fileSize - LastPointerEnd;
	while (toCopy >= bufferSize)
	{
		ifile.read(buffer, bufferSize);
		ofile.write(buffer, bufferSize);
		toCopy -= bufferSize;
	}
	{
		ifile.read(buffer, toCopy);
		ofile.write(buffer, toCopy);
		toCopy = 0;
	}

	ifile.close();
	ofile.close();
	LastPointerBegin = -1;
	LastPointerEnd = -1;

	std::remove(PathText.c_str());

	if (std::rename(backupFile.c_str(), PathText.c_str()) == 0)
		return 0;
	else
		return ERROR::RenamingError;
}


void DataBase::AddMessage(Message message)
{
    MemoryBase.push_back(message);
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


Message DataBase::GetByIdText(int id)
{
	ReadText(id);
	for (auto& i : MemoryBase)
	{
		if (i.ID == id)
		{
			return i;
		}
	}
	return Message();
}

Message DataBase::GetByIdBin(int id)
{
	ReadBin(id);
	for (auto& i : MemoryBase)
	{
		if (i.ID == id)
		{
			return i;
		}
	}
	return Message();
}

void DataBase::SetDeafaultBinPath()
{
	PathBin = "D:\\DataBase.bin";
}

void DataBase::SetDeafaultTextPath()
{
	PathText = "D:\\DataBase.txt";
}

void DataBase::SetBinPath(std::string path)
{
	PathBin = path;
}

void DataBase::SetTextPath(std::string path)
{
	PathText = path;
}
