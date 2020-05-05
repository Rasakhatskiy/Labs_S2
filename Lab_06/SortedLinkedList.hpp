#ifndef SORTED_LINKED_LIST_HHPP
#define LIST_HPP
#include <stdexcept>
#include <string>


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


class SortedLinkedList
{
public:
	//calls create empty
	SortedLinkedList();

	//
	~SortedLinkedList();

	//Creates an empty list or just clears current
	void CreateEmpty();

	//Returns current number of nodes in list
	int Length();

	//Inserts element BEFORE index
	void Insert(std::string element, int index);

	void Insert(std::string value);

	//Removes element at position
	void Remove(int index);

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

	int Search(std::string value);

private:

	//Root node of list
	Node* Root;

	//true if error ocurred
	bool Error = false;

	//Shown size to user
	int Size = 0;
};


#endif // !LIST_HPP

