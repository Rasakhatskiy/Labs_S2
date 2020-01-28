#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "..\Include\Message.hpp"

#include <vector>
#include <string>
#include <fstream>

class DataBase
{
    const std::string PathText = "D:\\DataBase.txt";
    const std::string PathBin = "D:\\DataBase.bin";
    unsigned int MaxID = 0;
    std::vector<int> IDs;
public:
    std::vector<Message> MemoryBase;
    int SaveToText();
    int LoadFromBin();
    int ReadBin();
    int SaveToBin();
    int ReadIDs();
    DataBase();
    ~DataBase();

    
    void AddMessage(Message message);
};

#endif //DATABASE_HPP



