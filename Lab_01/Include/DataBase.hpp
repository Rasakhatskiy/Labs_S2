#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "..\Include\Message.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstdio>
#include <filesystem>

class DataBase
{
    std::string PathText = "D:\\DataBase.txt";
    std::string PathBin = "D:\\DataBase.bin";
    const unsigned int I_LOVE_KNU_EXCEPT_MATAN = 0x5849584B; //Inversed KXIX -> XIXK
    unsigned int MaxID_BIN = 0;
    unsigned int MaxID_TXT = 0;
    unsigned int MaxElements = 0;
    std::vector<int> IDs;
public:
	DataBase();
	~DataBase();

    std::vector<Message> MemoryBase;
	int LastPointerBegin = -1;
	int LastPointerEnd = -1;


	int ReadIDsBin();
	int ReadIDsText();

	int ReadBin(int searchId = -1);
	int ReadText(int searchId = -1);

    int SaveMemoryToText();
	int SaveMemoryToBin();

	int AppendToBin (Message message, int id = -1);
	int AppendToText(Message message, int id = -1);
    
	int ShiftDataBaseBin();
	int ShiftDataBaseText();
    
    void AddMessage(Message message);
	int ReadIdDate(std::string source, unsigned& id, DateTime& datetime);
	int SearchByText(std::string fragment);
	int SearchRateAuthor(std::string author, float rateMin, float rateMax);
	int SearchTypeTime(Message::MessageType type, DateTime dateTimeBefore);
	Message GetByIdText(int id);
	Message GetByIdBin(int id);

	void SetDeafaultBinPath();
	void SetDeafaultTextPath();
	void SetBinPath(std::string path);
	void SetTextPath(std::string path);

	

};

inline bool FileExists(const std::string& name)
{
	std::ifstream f(name.c_str());
	return f.good();
}

#endif //DATABASE_HPP



