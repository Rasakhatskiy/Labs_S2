#include "../Include/Interaction.hpp"



int SIZE_M_POINT = 1;
Point3D* MOTHER_ARRAY_POINT = new Point3D[SIZE_M_POINT];

int SIZE_M_MESSAGE = 1;
Message* MOTHER_ARRAY_MESSAGE = new Message[SIZE_M_MESSAGE];

std::default_random_engine randomEngine
(std::chrono::steady_clock::now().time_since_epoch().count());

std::uniform_int_distribution<int> intRandomGenerator{ INT16_MIN, INT16_MAX };
std::uniform_int_distribution<int> intPositiveRandomGenerator{ 0, INT16_MAX };
std::uniform_int_distribution<int> intRandomGenerator5{ 0, 5 };

//----------------------------------PRINTING ARRAYS-------------------------------------
void PrintArray(Point3D* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "(" << arr[i].X << " " << arr[i].Y << " " << arr[i].Z << ")" << std::endl;
	}
	std::cout << std::endl;
}

void PrintArray(Message* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		PrintMessage(arr[i]);
	}
	std::cout << std::endl;
}

void PrintMessage(Message message)
{
	std::cout << "\n-----Message [" << message.ID << "][" << message.Time.ToString() << "]-----------------------------------\n";
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


int ReadPositiveInteger()
{
	int x;
	std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Invalid input! Enter positive integer! Not a character, INTEGER!!! It may look like this: 47" << std::endl;
		std::cout << "If it looks like Ɉɛɱɢɫɥɢɬɢ or -1, please, call exorcist." << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	return x;
}

void LaunchBenchmark()
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;
	auto maxTime = 0.0;

	int elements = 10000;

	do 
	{
		std::cout << std::endl;
		elements *= 10;
		std::cout << "Creating array of " << elements << " elements" << std::endl;

		SilentShufflePoint3D(elements);
		Point3D* arr = new Point3D[SIZE_M_POINT];


		for (int i = 0; i < SIZE_M_POINT; i++) arr[i] = MOTHER_ARRAY_POINT[i];
		
		begin = std::chrono::steady_clock::now();
		InsertionSort(arr, 0, SIZE_M_POINT - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Insertion sort time: "<< time<< " miliseconds" << std::endl;
		if (time > maxTime)
			maxTime = time;

		for (int i = 0; i < SIZE_M_POINT; i++) arr[i] = MOTHER_ARRAY_POINT[i];

		begin = std::chrono::steady_clock::now();
		QuickSort(arr, 0, SIZE_M_POINT - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Quick sort time: " << time << " miliseconds" << std::endl;
		if (time > maxTime) maxTime = time;

		for (int i = 0; i < SIZE_M_POINT; i++) arr[i] = MOTHER_ARRAY_POINT[i];

		begin = std::chrono::steady_clock::now();
		MergeSort(arr, 0, SIZE_M_POINT - 1);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Merge sort time: " << time << " miliseconds" << std::endl;
		if (time > maxTime) maxTime = time;

		delete[] arr;
	} while (maxTime < 10000);


}


//----------------------------------EVERYDAY AM SHUFFELING------------------------------
void ShufflePoint3D()
{
	std::cout << std::endl;
	std::cout << "Enter array size : ";
	SIZE_M_POINT = ReadPositiveInteger();
	delete[] MOTHER_ARRAY_POINT;
	MOTHER_ARRAY_POINT = new Point3D[SIZE_M_POINT];

	double max = (INT16_MAX / 8.0);
	double min = (INT16_MIN / 8.0);

	double x, y, z, f;

	srand(time(NULL));
	for (int i = 0; i < SIZE_M_POINT; i++)
	{
		f = (double)rand() / RAND_MAX;
		x = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		y = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		z = min + f * (max - min);

		Point3D point = Point3D(x, y, z);
		MOTHER_ARRAY_POINT[i] = point;
	}
	if (SIZE_M_POINT < 1024)
		PrintArray(MOTHER_ARRAY_POINT, SIZE_M_POINT);
	else
		std::cout << "Your monitor is to small to fit " << SIZE_M_POINT << " elements. Please purchase compatible monitor." << std::endl;

	//mama mia system pause oh no shit what i have to do
	std::cout << "Pres eni ki to kontinue.,." << std::endl;
	_getch();
}

void SilentShufflePoint3D(int size)
{
	SIZE_M_POINT = size;
	delete[] MOTHER_ARRAY_POINT;
	MOTHER_ARRAY_POINT = new Point3D[SIZE_M_POINT];

	double max = (INT16_MAX / 8.0);
	double min = (INT16_MIN / 8.0);

	double x, y, z, f;

	srand(time(NULL));
	for (int i = 0; i < SIZE_M_POINT; i++)
	{
		f = (double)rand() / RAND_MAX;
		x = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		y = min + f * (max - min);
		f = (double)rand() / RAND_MAX;
		z = min + f * (max - min);

		Point3D point = Point3D(x, y, z);
		MOTHER_ARRAY_POINT[i] = point;
	}
}

void ShuffleMessages()
{
	std::cout << std::endl;
	std::cout << "Enter array size : ";
	SIZE_M_MESSAGE = ReadPositiveInteger();
	delete[] MOTHER_ARRAY_MESSAGE;
	MOTHER_ARRAY_MESSAGE = new Message[SIZE_M_MESSAGE];

	for (int i = 0; i < SIZE_M_MESSAGE; i++)
	{
		MOTHER_ARRAY_MESSAGE[i] = GetRandomMessage();
	}

	if (SIZE_M_MESSAGE < 100)
		PrintArray(MOTHER_ARRAY_MESSAGE, SIZE_M_MESSAGE);
	else
		std::cout << "It is too mush for me to print " << SIZE_M_MESSAGE << " elements. Pls forgive me." << std::endl;

	std::cout << "Press the power button to shut down your PC..." << std::endl;
	_getch();
}

//----------------------------------GENERATING MESSAGE----------------------------------
Message GetRandomMessage()
{
	Message message = Message();
	std::uniform_int_distribution<int> randDist{ 0, INT32_MAX };
	message.ID = intPositiveRandomGenerator(randomEngine);
	message.Text = GetRandomText();
	message.Author = GetRandomAuthor();
	message.Recipient = GetRandomRecipient();
	message.Time = DateTime(randDist(randomEngine));
	message.Type = Message::MessageType(intRandomGenerator5(randomEngine));
	message.Rate = (intPositiveRandomGenerator(randomEngine));
	return message;
}

std::string GetRandomText()
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
	std::uniform_int_distribution<int> randDist{ 0, (int)(words.size() - 1) };
	int numberOfWords = randDist(randomEngine);

	for (int i = 0; i < numberOfWords; i++)
	{
		int number = randDist(randomEngine);
		text += words[number] + " ";
	}
	text += "\n";
	return text;
}

std::string GetRandomAuthor()
{
	std::string randText = RANDOM_AUTHOR;
	std::vector<std::string> words;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = randText.find(delimiter)) != std::string::npos) 
	{
		words.push_back(randText.substr(0, pos));
		randText.erase(0, pos + delimiter.length());
	}
	std::uniform_int_distribution<int> randDist{ 0, (int)(words.size() - 1) };
	return words[randDist(randomEngine)];
}

std::string GetRandomRecipient()
{
	std::string randText = RANDOM_RECIPIENT;
	std::vector<std::string> words;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = randText.find(delimiter)) != std::string::npos) 
	{
		words.push_back(randText.substr(0, pos));
		randText.erase(0, pos + delimiter.length());
	}
	std::uniform_int_distribution<int> randDist{ 0, (int)(words.size() - 1) };
	return words[randDist(randomEngine)];
}

