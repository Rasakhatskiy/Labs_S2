#ifndef SORTED_LINKED_LIST_HHPP
#define SORTED_LINKED_LIST_HHPP
#include <stdexcept>
#include <string>

#include "ArrangedList.hpp"

struct Node
{
	std::string Value;
	Node* Next;
	Node(std::string value, Node* next)
	{
		Value = value;
		Next = next;
	}
	Node() { ; }
	~Node() { ; }
};


class SortedLinkedList : public ArrangedList
{
public:
	//calls create empty
	SortedLinkedList();

	//
	~SortedLinkedList();

	//Returns current number of nodes in list
	int Length();

	//Inserts element BEFORE index
	void Insert(std::string element, int index);

	void Insert(std::string value);
	void Remove(std::string value);
	std::vector<std::string> ToVectorValues();
	bool Search(std::string value);


	//Retuns element by id, returns NULL if there's no such id
	std::string Get(int index);

	//Replaces element at index with given element
	void Set(std::string element, int index);

	//returns root node pointer
	Node* GetRoot();

	//returns error state
	bool IsError();

	//Sets Error to false
	void ResetError();

	//Returns emptyness condition
	bool IsEmpty();

	//Returns size of all structure
	int GetSize()
	{
		return
			sizeof(Node) * Size +
			sizeof(Size) +
			sizeof(Error);
	}


	void GetValueToVector(Node* node, std::vector<std::string>& vector);

private:

	//Root node of list
	Node* Root;

	//true if error ocurred
	bool Error = false;

	//Shown size to user
	int Size = 0;
};


#endif // !LIST_HPP

