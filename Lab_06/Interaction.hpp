#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "SortedLinkedList.hpp"			//SLL
#include "SortedArrayList.hpp"			//SAL
#include "SortedBinarySearchTree.hpp"	//BST
#include "Sorted_2_3_Tree.hpp"			//TTT
#include "SortedAvlTree.hpp"			//AVL

#include "ArrangedList.hpp"

#include <iostream>
#include <conio.h> //pls forgive me for what i'm about to do
#include <chrono>
#include <thread>
#include <random>


ArrangedList* AR;

std::random_device RandomDevice;
std::mt19937 RandomGenerator;
std::uniform_int_distribution<int> RandomDistributorInt;
std::uniform_int_distribution<int> RandomDistributorInt25;

void InitRandom()
{
	RandomGenerator = std::mt19937(RandomDevice());
	RandomDistributorInt = std::uniform_int_distribution<int>(32, 128);
	RandomDistributorInt25 = std::uniform_int_distribution<int>(1, 25);
}

void Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void SleepShort()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(666));
}

char GetRandomChar()
{
	return (char)RandomDistributorInt(RandomGenerator);
}

int GetRandomLength()
{
	return RandomDistributorInt25(RandomGenerator);
}

bool CheckList()
{
	if (!AR)
	{
		std::cout << "Create list first\n..." << std::endl;
		_getch();
		return false;
	}
	return true;
}

void SLL_Create()
{
	AR = new SortedLinkedList();
}
void SAL_Create()
{
	AR = new SortedArrayList();
}
void BST_Create()
{
	AR = new SortedBinarySearchTree();
}
void TTT_Create()
{
	AR = new Sorted_2_3_Tree();
}
void AVL_Create()
{
	AR = new SortedAvlTree();
}

void Insert()
{
	if (!CheckList()) return;
	std::cout << "Enter string to insert:" << std::endl;
	std::string value;
	std::getline(std::cin, value);
	AR->Insert(value);
}

void Remove()
{
	if (!CheckList()) return;
	std::cout << "Enter string to remove:" << std::endl;
	std::string value;
	std::getline(std::cin, value);
	AR->Remove(value);
}

void Search()
{
	if (!CheckList()) return;
	std::cout << "Enter string to search:" << std::endl;
	std::string value;
	std::getline(std::cin, value);
	if (AR->Search(value))
		std::cout << "Value found." << std::endl;
	else
		std::cout << "Value not found." << std::endl;

	std::cout << "_getch()" << std::endl;
	_getch();
}

void Show()
{
	if (!CheckList()) return;
	auto vector = AR->ToVectorValues();
	for (auto& i : vector) std::cout << i << std::endl;
	std::cout << std::endl;
	std::cout << "..." << std::endl;
	_getch();
}


void Demo()
{
	std::cout << "Creating list with 25 random strings" << std::endl;
	AR = new SortedLinkedList();
	for (int i = 0; i < 25; ++i)
	{
		std::string string;
		auto length = GetRandomLength();
		for (int j = 0; j < length; ++j)
			string += GetRandomChar();
		AR->Insert(string);
	}
	Sleep();
	std::cout << "Here is it : " << std::endl;
	auto vector = AR->ToVectorValues();
	for (auto& i : vector) std::cout << i << std::endl;
	std::cout << std::endl;

	Sleep();
	std::cout << "Let's remove some random elements" << std::endl;

	for (int i = 0; i < 10; i++)
	{
		auto randomShit = std::uniform_int_distribution<int>(1, (24 - i));
		auto index = randomShit(RandomGenerator);
		std::cout << "Removing " << vector[index] << std::endl;
		AR->Remove(vector[index]);
		vector = AR->ToVectorValues();
		SleepShort();
	}
	Sleep();
	std::cout << "\n\nHere is new array : " << std::endl;
	vector = AR->ToVectorValues();
	for (auto& i : vector) std::cout << i << std::endl;
	std::cout << std::endl;
	Sleep();
	std::cout << "I think there is no sense to test seach here, but let's search for a Duck :" << std::endl;
	
	Sleep(); std::cout << "...\n";
	Sleep(); std::cout << "...\n";
	Sleep(); std::cout << "...\n";
	Sleep(); std::cout << "...\n";

	if (AR->Search("Duck"))
		std::cout << "Impossible, but duck was found, you are lucky today!" << std::endl;
	else
		std::cout << "Duck wasn't found, never lucky :(" << std::endl;

	std::cout << "Press any Duck to continue..." << std::endl;
	_getch();
};

void Benchmark() {};
#endif // !INTERACTION_HPP

