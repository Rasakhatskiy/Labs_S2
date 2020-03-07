#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>

template <typename Type>
class List
{
public:
	//calls create empty
	List<Type>();

	//
	~List();
	
	//Creates an empty list or just clears current
	void CreateEmpty();

	//Returns current number of nodes in list
	int Length();

	//Inserts element BEFORE index
	void Insert(Type element, int index);

	//Removes element at position
	void Remove(int index);

	//Retuns element by id, returns NULL if there's no such id
	Type Get(int index);

	//Replaces element at index with given element
	void Set(Type element, int index);

	bool IsError();

private:
	struct Node
	{
		Type Value;
		Node* Next;

		Node(Type value, Node* next)
		{
			Value = value;
			Next = next;
		}

		Node() = default;
	};

	Node* Root;

	//minimal real size of dynamic array
	const int MIN_REAL_SIZE = 16;

	//true if error ocurred
	bool Error = false;

	//Real size of dynamic array
	int RealSize;

	//Shown size to user
	int Size;
};

template <typename Type>
void List<Type>::CreateEmpty()
{
	Size = 0;
	RealSize = MIN_REAL_SIZE;
	Root = new Node();
	Root->Next = Root;
}

template<typename Type>
int List<Type>::Length()
{
	return Size;
}

template<typename Type>
void List<Type>::Insert(Type value, int index)
{
	try 
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		else
		{
			if (Size == 0)
			{
				Root->Value = value;
				Size++;
				return;
			}
			if (index == 0)
			{
				Node* newRoot = new Node(value, Root);
				Node* temp = Root;
				while (temp->Next != Root)
					temp = temp->Next;
				temp->Next = newRoot;
				Root = newRoot;
			}
			else
			{
				int count = 1;
				Node* prev = Root;
				while (count != index)
				{
					prev = prev->Next;
					count++;
				}
				Node* temp = new Node(value, prev->Next);
				prev->Next = temp;
			}
			Size++;
		}
	}
	catch (...)
	{
		Error = true;
	}

	return;
}

template<typename Type>
void List<Type>::Remove(int index)
{
	//todo
}

template<typename Type>
Type List<Type>::Get(int index)
{
	//todo
	return Type();
}

template<typename Type>
void List<Type>::Set(Type element, int index)
{
	//todo
}


template<typename Type>
bool List<Type>::IsError()
{
	return Error;
}


template <typename Type>
List<Type>::List()
{
	CreateEmpty();
}

template<typename Type>
List<Type>::~List()
{
}
#endif // !LIST_HPP

