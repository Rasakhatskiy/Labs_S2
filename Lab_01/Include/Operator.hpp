#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "..\Include\Message.hpp"
#include "..\Include\DateTime.hpp"
#include "..\Include\DataBase.hpp"
#include "..\Include\Error.hpp"


#include <vector>
#include <iostream>
#include <conio.h>
#include <ctime>

class Operator
{
private:
    DataBase _DataBase;

    Message ReadMessage();

    std::string ReadStringMultiLine();
    std::string ReadStringShort();

    Message::MessageType ReadMessageType();

    DateTime ReadDateTime();

    double ReadDouble();
    void PrintMessage(int id, Message message);
    bool IsValidStringName(std::string name);

    void PrintError(int errorID);
	void ClearScreen();

    

public:
	void Add();
	void LoadIDs();

    void SaveText();
    void SaveBin();

	void LoadBin();
	void LoadText();

	void SearchText();
	void SerchRateAuthor();
	void SearchTypeTime();


	void ModifyText();
	void ModifyBin();
	void DeleteText();
	void DeleteBin();
	void Demo();
	void Benchmark();

	std::string GetRandomText();

    void PrintMemory();

    Operator();
    ~Operator();


};

#endif //OPERATOR_HPP
