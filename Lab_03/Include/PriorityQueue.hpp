#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <string>

template <typename Type>
struct Node
{
	Type Value;
	Node<Type>* Next;
	int Priority;
	Node(Type value, int priority, Node* next)
	{
		Value = value;
		Priority = priority;
		Next = next;
	}
	Node() { ; }
	~Node() { ; }
};

template <typename Type>
class PriorityQuiue
{
public:
	//calls create empty
	PriorityQuiue<Type>();

	//
	~PriorityQuiue();
	
	//Creates an empty list or just clears current
	void CreateEmpty();

	//Returns current number of nodes in list
	int Length();

	//Inserts element BEFORE index
	void Push(Type element, int priority);

	//Removes element at position
	Type Pop();

	//Retuns element by id, returns NULL if there's no such id
	Type Get(int index);

	//Replaces element at index with given element
	void Set(Type element, int index);

	//returns root node pointer
	Node<Type>* GetRoot();

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
			(sizeof(Node<Type>*) * 2 + sizeof(Type)) * Size +
			sizeof(Size) +
			sizeof(Error);
	}

private:
	
	//Root node of list
	Node<Type>* Root;

	//true if error ocurred
	bool Error = false;

	//Shown size to user
	int Size = 0;
};

template <typename Type>
void PriorityQuiue<Type>::CreateEmpty()
{
	if (Size != 0)
	{
		auto current = Root;
		while(current != nullptr)
		{
			auto next = current->Next;
			delete current;
			current = next;
		}
		delete Root;
	}
	Size = 0;
	Error = false;
	Root = new Node<Type>();
	Root->Next = nullptr;
}

template<typename Type>
int PriorityQuiue<Type>::Length()
{
	return Size;
}

template<typename Type>
void PriorityQuiue<Type>::Push(Type value, int priority)
{
	try 
	{
		if (Size == 0)
		{
			Root->Value = value;
			Root->Priority = priority;
			Root->Next = nullptr;
			Size++;
			return;
		}
		
		if (priority < Root->Priority)
		{
			auto node = new Node<Type>(value, priority, Root);
			Root = node;
			Size++;
			return;
		}

		auto current = Root;
		while (current->Next != nullptr && priority >= current->Next->Priority)
		{
			current = current->Next;
		}
		auto next = current->Next;
		current->Next = new Node<Type>(value, priority, next);
		Size++;
	}
	catch (...)
	{
		Error = true;
	}

	return;
}

template<typename Type>
Type PriorityQuiue<Type>::Pop()
{
	try
	{
		if (Size == 0)
		{
			throw std::out_of_range("Queue is empty");
		}
		if (Size == 1)
		{
			auto value = Root->Value;
			delete Root;
			Size--;
			return value;
		}
		{
			auto value = Root->Value;
			auto node = Root;
			Root = Root->Next;
			delete node;
			Size--;
			return value;
		}
	}
	catch (...)
	{
		Error = true;
	}
	return NULL;
}

template<typename Type>
Type PriorityQuiue<Type>::Get(int index)
{
	try
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		if (Size == 0)
		{
			throw std::out_of_range("List is empty");
		}
		int count = 0;
		auto seek = Root;
		while (count != index)
		{
			seek = seek->Next;
			count++;
		}
		return seek->Value;
	}
	catch (...)
	{
		Error = true;
	}
}

template<typename Type>
void PriorityQuiue<Type>::Set(Type value, int index)
{
	try
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		if (Size == 0)
		{
			throw std::out_of_range("List is empty");
		}
		int count = 0;
		auto seek = Root;
		while (count != index)
		{
			seek = seek->Next;
			count++;
		}
		seek->Value = value;
	}
	catch (...)
	{
		Error = true;
	}
}

template<typename Type>
bool PriorityQuiue<Type>::IsError()
{
	return Error;
}

template<typename Type>
inline void PriorityQuiue<Type>::ResetError()
{
	Error = false;
}

template<typename Type>
inline bool PriorityQuiue<Type>::IsEmpty()
{
	return Size == 0;
}

template <typename Type>
PriorityQuiue<Type>::PriorityQuiue()
{
	CreateEmpty();
}

template <typename Type> 
Node<Type>* PriorityQuiue<Type>::GetRoot()
{
	return Root;
}

template<typename Type>
PriorityQuiue<Type>::~PriorityQuiue()
{
}
#endif // !LIST_HPP

