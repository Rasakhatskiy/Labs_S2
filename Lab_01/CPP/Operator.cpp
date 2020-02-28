#include "..\Include\Operator.hpp"
#include "..\Include\RandomText.hpp"
void Operator::Add()
{
	auto message = ReadMessage();
	_DataBase.AppendToBin(message);
	ClearScreen();
	PrintMessage(0, message);
	std::cout << "***Saved to disk***" << std::endl;
	system("pause");
}

void Operator::SaveText()
{
    if (_DataBase.SaveMemoryToText() == 0)
        std::cout << "***Saved***" << std::endl;
    else
        std::cerr << "***Error***" << std::endl;

    system("pause");
}

void Operator::SaveBin()
{

    /*int result = _DataBase.SaveToBin();
        if (result == 0)
            std::cout << "***Saved tobinary file***" << std::endl;
        else
            PrintError(result);*/

    system("pause");
}


void Operator::LoadBin()
{
    int result = _DataBase.ReadBin();

    if (result == 0)
        std::cout << "***Loaded to memory***" << std::endl;
    else
        PrintError(result);

    system("pause");
}

void Operator::LoadText()
{
	int result = _DataBase.ReadText();

	if (result == 0)
		std::cout << "***Loaded to memory***" << std::endl;
	else
		PrintError(result);

	system("pause");
}


void Operator::SearchText()
{
	std::cout << "\nEnter fragment for search : \n";
	std::string fragment;
	std::getline(std::cin, fragment);
	_DataBase.SearchByText(fragment);
	PrintMemory();
}

void Operator::SerchRateAuthor()
{
	float min, max;

	std::cout << "\nEnter author for search : \n";
	std::string author = ReadStringShort();

	std::cout << "Enter minimum rate: ";
	std::cin >> min;

	std::cout << "Enter maximum rate: ";
	std::cin >> max;

	_DataBase.SearchRateAuthor(author, min, max);
	PrintMemory();
}

void Operator::SearchTypeTime()
{
	Message::MessageType type;
	DateTime datetime;

	std::cout << "\nEnter message type : \n";
	type = ReadMessageType();

	std::cout << "Enter maximum date :\n";
	datetime = ReadDateTime();

	_DataBase.SearchTypeTime(type, datetime);
	PrintMemory();
}


Message Operator::ReadMessage()
{
    Message message = Message();
    message.ID = 0;
    message.Text = ReadStringMultiLine();
	std::cout << std::endl;

    message.Time = ReadDateTime();
	std::cout << std::endl;

    std::cout << "Enter author name" << std::endl;
    message.Author = ReadStringShort();
	std::cout << std::endl;

    std::cout << "Enter recipient name" << std::endl;
    message.Recipient = ReadStringShort();
	std::cout << std::endl;

    message.Type = ReadMessageType();
	std::cout << std::endl;

    message.Rate = ReadDouble();
	std::cout << std::endl;

    return message;
}

void Operator::LoadIDs()
{
    _DataBase.ReadIDsBin();
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

void Operator::PrintError(int errorID)
{
    std::cerr << "Error : " << GetError(errorID) << std::endl;
}

void Operator::ClearScreen()
{
    system("CLS");
}


void Operator::ModifyText()
{
	int ID;
	Message message;
	bool done = false;

	while (!done)
	{
		std::cout << "Enter ID to modify : ";
		std::cin >> ID;
		message = _DataBase.GetByIdText(ID);
		if (message.ID == -1)
		{
			std::cout << "Message not found!" << std::endl;
		}
		else
		{
			done = true;
		}
	}

	PrintMessage(message.ID, message);
	message.Text = ReadStringMultiLine();
	message.Rate = ReadDouble();

	int error = _DataBase.ShiftDataBaseText();

	if (error == 0)
	{
		_DataBase.AppendToText(message, message.ID);
		std::cout << "***Saved to text file***" << std::endl;
	}
	else
	{
		PrintError(error);
	}
}

void Operator::ModifyBin()
{
	int ID;
	Message message;
	bool done = false;

	while (!done)
	{
		std::cout << "Enter ID to modify : ";
		std::cin >> ID;
		message = _DataBase.GetByIdBin(ID);
		if (message.ID == -1)
		{
			std::cout << "Message not found!" << std::endl;
		}
		else
		{
			done = true;
		}
	}

	PrintMessage(message.ID, message);
	message.Text = ReadStringMultiLine();
	message.Rate = ReadDouble();

	int error = _DataBase.ShiftDataBaseBin();

	if (error == 0)
	{
		_DataBase.AppendToBin(message, message.ID);
		std::cout << "***Saved to binary file***" << std::endl;
	}
	else
	{
		PrintError(error);
	}
}


void Operator::DeleteText()
{

}

void Operator::DeleteBin()
{

}


void Operator::Demo()
{
	//Add random messages
	//Print
	//Save to disk
	//Search by word "told"
	//Search by author Kakyoin
	//Search invites
	const int NUMBER_OF_MESSAGES = 13;
	const std::string SEARCH_WORD = "told";
	const std::string SEARCH_AUTHOR = "Kakyoin";
	const Message::MessageType SEARCH_Type = Message::MessageType::Invite;

	//Step 1 - create messages and read them
	{
		std::cout << "***Demo mode powered on***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "***Turning on jet engines***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "***Launching nuclear missiles***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "***Generating " << NUMBER_OF_MESSAGES << " random messages***" << std::endl;

		for (int i = 0; i < NUMBER_OF_MESSAGES; i++)
			_DataBase.AppendToBin(GetRandomMessage());
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "***Saved on disk***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		//LoadBin();
		//no press any key
		{
			int result = _DataBase.ReadBin();
			if (result == 0) std::cout << "***Loaded to memory***" << std::endl;
			else PrintError(result);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "----NOW READ! QUICK! YOU HAVE 5 SECONDS" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		//PrintMemory();
		//no press any key
		{
			for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
				PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(6000));
		system("CLS");

		std::cout << "----ACTUALLY THIS WAS 6 SECONDS----" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));

		std::cout << "----OK, OK, I WILL GIVE YOU MORE TIME----" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		//PrintMemory();
		//no press any key
		{
			for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
				PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
		}
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		system("pause");
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		system("CLS");
		std::cout
			<< "You have wasted "
			<< std::chrono::duration_cast<std::chrono::seconds>(end - begin).count()
			<< " seconds of your life to read these messages." << std::endl;
		system("pause");
		system("CLS");
	}

	//Step 2 - search
	{
		std::cout << "***Now let's search for word \"" << SEARCH_WORD << "\"***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		_DataBase.SearchByText(SEARCH_WORD);
		
		std::cout << "***Here is what i found***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		{
			for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
				PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
		}
		system("pause");
		system("CLS");

		std::cout << "***Now let's search for author \"" << SEARCH_AUTHOR << "\"***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		_DataBase.SearchRateAuthor(SEARCH_AUTHOR, 0, 100000000);

		std::cout << "***Here is what i found***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		{
			for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
				PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
		}
		system("pause");
		system("CLS");

		std::cout << "***Now let's search for invites***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		_DataBase.SearchTypeTime(SEARCH_Type, DateTime(3000, 12, 12, 59, 59, 59));

		std::cout << "***Here is what i found***" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		{
			for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
				PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
		}
		system("pause");
		system("CLS");
	}
}

void Operator::Benchmark()
{
	int NUMBER_OF_MESSAGES = 10;
	bool flag = true;
	const std::string SEARCH_WORD = "told";
	const std::string SEARCH_AUTHOR = "Kakyoin";
	const Message::MessageType SEARCH_Type = Message::MessageType::Invite;

	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

	std::cout << "***Benchmark mode powered on***" << std::endl;
	while (flag)
	{
		//Generate to memory
		{
			std::cout << "***Generating " << NUMBER_OF_MESSAGES << " random messages***" << std::endl;
			begin = std::chrono::steady_clock::now();
			for (int i = 0; i < NUMBER_OF_MESSAGES; i++)
				_DataBase.MemoryBase.push_back(GetRandomMessage());
			end = std::chrono::steady_clock::now();

			std::cout << "***Saved to memory***" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;

			if (std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() > 10)
				flag = false;

			int totalSize = 0;
			for (auto& i : _DataBase.MemoryBase)
				totalSize += i.GetSize();

			std::cout
				<< "Memory taken: "
				<< totalSize / 1024.0
				<< " KB" << std::endl;
			std::cout << std::endl;
		}

		//Save on disk
		{
			auto begin = std::chrono::steady_clock::now();
			_DataBase.SaveMemoryToBin();
			auto end = std::chrono::steady_clock::now();

			std::cout << "***Saved on disk***" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;
			std::cout << std::endl;
		}

		//Read from disk
		{
			begin = std::chrono::steady_clock::now();
			_DataBase.ReadBin();
			end = std::chrono::steady_clock::now();

			std::cout << "***Loaded from disk***" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;
			std::cout << std::endl;
		}

		//Search
		{
			std::cout << "***Now let's search for word \"" << SEARCH_WORD << "\"***" << std::endl;
			begin = std::chrono::steady_clock::now();
			_DataBase.SearchByText(SEARCH_WORD);
			end = std::chrono::steady_clock::now();
			std::cout << "Found " << _DataBase.MemoryBase.size() << " elements" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;
			std::cout << std::endl;

			std::cout << "***Now let's search for author \"" << SEARCH_AUTHOR << "\"***" << std::endl;
			begin = std::chrono::steady_clock::now();
			_DataBase.SearchRateAuthor(SEARCH_AUTHOR, 0, 100000000);
			end = std::chrono::steady_clock::now();
			std::cout << "Found " << _DataBase.MemoryBase.size() << " elements" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;
			std::cout << std::endl;



			std::cout << "***Now let's search for invites***" << std::endl;
			begin = std::chrono::steady_clock::now();
			_DataBase.SearchTypeTime(SEARCH_Type, DateTime(3000, 12, 12, 59, 59, 59));
			end = std::chrono::steady_clock::now();
			std::cout << "Found " << _DataBase.MemoryBase.size() << " elements" << std::endl;
			std::cout
				<< "Elapsed time: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0
				<< " seconds" << std::endl;
			std::cout << std::endl;
		}
		system("pause");

		std::cout << "\n\n\n";
		NUMBER_OF_MESSAGES *= 10;
	}
	
}


std::string Operator::GetRandomText()
{
	std::string randText = RANDOM_LARGE_TEXT;
	std::vector<std::string> words;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = randText.find(delimiter)) != std::string::npos) {
		words.push_back(randText.substr(0, pos));
		randText.erase(0, pos + delimiter.length());
	}

	std::string text = "\n";

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, words.size() - 1); // define the range

	int numberOfWords = (distr(eng));

	for (int i = 0; i < numberOfWords; i++)
	{
		int number = (distr(eng));
		
		text += words[number] + " ";
	}
	text += "\n";
	return text;
}

std::string Operator::GetRandomAuthor()
{
	std::string randText = RANDOM_AUTHOR;
	std::vector<std::string> words;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = randText.find(delimiter)) != std::string::npos) {
		words.push_back(randText.substr(0, pos));
		randText.erase(0, pos + delimiter.length());
	}

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, words.size() - 1); // define the range

	return words[distr(eng)];
}

std::string Operator::GetRandomRecipient()
{
	std::string randText = RANDOM_RECIPIENT;
	std::vector<std::string> words;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = randText.find(delimiter)) != std::string::npos) {
		words.push_back(randText.substr(0, pos));
		randText.erase(0, pos + delimiter.length());
	}

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, words.size() - 1); // define the range

	return words[distr(eng)];
}

Message Operator::GetRandomMessage()
{
	Message message = Message();
	message.ID = 0;
	message.Text = GetRandomText();
	message.Author = GetRandomAuthor();
	message.Recipient = GetRandomRecipient();
	message.Time = DateTime(rand() % INT32_MAX - (INT32_MAX / 2));
	message.Type = Message::MessageType(rand() % 5);
	message.Rate = (rand() % UINT32_MAX);
	return message;
}

void Operator::PrintMemory()
{
	for (int i = 0; i < _DataBase.MemoryBase.size(); i++)
	{
		PrintMessage(_DataBase.MemoryBase[i].ID, _DataBase.MemoryBase[i]);
	}
	system("pause");
}

void Operator::PrintMessage(int id, Message message)
{
	std::cout << "\n-----Message [" << id << "][" << message.Time.ToString() << "]-----------------------------------\n";
	std::cout << " -> Author : " + message.Author + "\n";
	std::cout << " <- Recipient : " + message.Recipient + "\n";

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
	std::cout << "   [" + type + "]\n";
	auto size = message.Text.size();
	int col = 0;
	for (int i = 0; i < size; i++)
	{
		std::cout << message.Text[i];
		col++;
		if (message.Text[i] == '\n')
		{
			std::cout << "#\t";
			col = 0;
		}
		if (col > 108)
		{
			std::cout << "\n#\t";
			col = 0;
		}
	}
	//std::cout << message.Text;
	std::cout << "\n   Spam rate : " << message.Rate << std::endl;
}


Operator::Operator()
{
    
}

Operator::~Operator()
{
}


