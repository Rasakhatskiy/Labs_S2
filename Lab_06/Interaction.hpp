#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "SortedLinkedList.hpp"			//SLL
#include "SortedArrayList.hpp"			//SAL
#include "SortedBinarySearchTree.hpp"	//BST
#include "Sorted_2_3_Tree.hpp"			//TTT
#include "SortedAvlTree.hpp"			//AVL

#include "ArrangedList.hpp"

#include <iostream>
#include <conio.h> //lord forgive me for what i'm about to do


ArrangedList* AR;

void Demo() {};
void Benchmark() {};




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
	std::cout << "Enter string to insert:" << std::endl;
	std::string value;
	std::getline(std::cin, value);
	AR->Insert(value);
}

void Remove()
{
	std::cout << "Enter string to remove:" << std::endl;
	std::string value;
	std::getline(std::cin, value);
	AR->Remove(value);
}

void Search()
{
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
	auto vector = AR->ToVectorValues();
	for (auto& i : vector) std::cout << i << std::endl;
	std::cout << std::endl;
	std::cout << "Sorry linux, i choose CONIO.H..." << std::endl;
	_getch();
}
#endif // !INTERACTION_HPP

