#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "..\Include\Message.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

class DataBase
{
    const std::string PathText = "D:\\DataBase.txt";
    const std::string PathBin = "D:\\DataBase.bin";
    const unsigned int I_LOVE_KNU_EXCEPT_MATAN = 0x5849584B; //Inversed KXIX -> XIXK
    unsigned int MaxID = 0;
    unsigned int MaxElements = 0;
    std::vector<int> IDs;
public:
    std::vector<Message> MemoryBase;
    int SaveMemoryToText();
    int ReadBin();
	int ReadText();
    int SaveMemoryToBin();
    int AppendToBin(Message message);
    int ReadIDs();
    DataBase();
    ~DataBase();

    
    void AddMessage(Message message);
	int ReadIdDate(std::string source, unsigned& id, DateTime& datetime);
	int SearchByText(std::string fragment);
	int SearchRateAuthor(std::string author, float rateMin, float rateMax);
	int SearchTypeTime(Message::MessageType type, DateTime dateTimeBefore);
};

#endif //DATABASE_HPP



