#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <string>

template <typename Type>
struct Node
{
	Type Value;
	Node<Type>* Next;
	Node(Type value, Node* next)
	{
		Value = value;
		Next = next;
	}
	Node() { ; }
};

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

	//returns root node pointer
	Node<Type>* GetRoot();

	bool IsError();

private:
	
	//Root node of list
	Node<Type>* Root;

	//true if error ocurred
	bool Error = false;

	//Shown size to user
	int Size = 0;
};

template <typename Type>
void List<Type>::CreateEmpty()
{
	while (Size != 0) Remove(0);
	Size = 0;
	Root = new Node<Type>();
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
		if (Size == 0)
		{
			Root->Value = value;
			Size++;
			return;
		}
		if (index == 0)
		{
			auto newRoot = new Node<Type>(value, Root);
			auto temp = Root;
			while (temp->Next != Root)
				temp = temp->Next;
			temp->Next = newRoot;
			Root = newRoot;
		}
		else
		{
			int count = 1;
			auto prev = Root;
			while (count != index)
			{
				prev = prev->Next;
				count++;
			}
			auto temp = new Node<Type>(value, prev->Next);
			prev->Next = temp;
		}
		Size++;
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
		if (index == 0)
		{
			auto iter = Root->Next;
			while (iter->Next != Root)
				iter = iter->Next;
			iter->Next = Root->Next;
			delete Root;
			Root = iter->Next;
		}
		else
		{
			int count = 1;
			auto prev = Root;
			while (count != index)
			{
				count++;
				prev = prev->Next;
			}
			//prev next

			auto current = prev->Next;
			auto next = current->Next;
			delete current;
			current = next;
			prev->Next = current;
		}
		Size--;
	}
	catch (...)
	{
		Error = true;
	}
	return;
}

template<typename Type>
Type List<Type>::Get(int index)
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
void List<Type>::Set(Type value, int index)
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
bool List<Type>::IsError()
{
	return Error;
}

template <typename Type>
List<Type>::List()
{
	CreateEmpty();
}

template <typename Type> 
Node<Type>* List<Type>::GetRoot()
{
	return Root;
}

template<typename Type>
List<Type>::~List()
{
}
#endif // !LIST_HPP

