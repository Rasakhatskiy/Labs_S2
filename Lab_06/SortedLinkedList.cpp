#include "SortedLinkedList.hpp"

SortedLinkedList::SortedLinkedList()
{
	CreateEmpty();
}

SortedLinkedList::~SortedLinkedList()
{
}


void SortedLinkedList::CreateEmpty()
{
	if (Root != nullptr)
	{
		auto current = Root->Next;
		while (current != Root)
		{
			auto next = current->Next;
			delete current;
			current = next;
		}
		delete Root;
	}
	Size = 0;
	Error = false;
	Root = nullptr;
}


int SortedLinkedList::Length()
{
	return Size;
}

void SortedLinkedList::Insert(std::string value, int index)
{
	try
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("Index out of range");
		}
		if (Root == nullptr)
		{
			Root = new Node(value, nullptr);
			Size++;
			return;
		}
		if (index == 0)
		{
			auto newRoot = new Node(value, Root);
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
			auto temp = new Node(value, prev->Next);
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

void SortedLinkedList::Insert(std::string value)
{
	try
	{
		if (Root == nullptr)
		{
			Root = new Node(value, nullptr);
			Size = 1;
			return;
		}
		Node* current = Root;
		Node* previous = nullptr;
		auto size = value.size();
		while (current != nullptr && current->Value.size() > size)
		{
			previous = current;
			current = current->Next;
		}
		if (current == nullptr)
			previous->Next = new Node(value, nullptr);
		else if (previous == nullptr)
			Root = new Node(value, Root);
		else
			previous->Next = new Node(value, current);

		Size++;
	}
	catch (...)
	{
		Error = true;
	}

	return;
}

void SortedLinkedList::Remove(int index)
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
		if (Size == 1)
		{
			delete Root;
			Size--;
			return;
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


std::string SortedLinkedList::Get(int index)
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

void SortedLinkedList::Set(std::string value, int index)
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

bool SortedLinkedList::IsError()
{
	return Error;
}

inline void SortedLinkedList::ResetError()
{
	Error = false;
}

inline bool SortedLinkedList::IsEmpty()
{
	return Size == 0;
}

int SortedLinkedList::Search(std::string value)
{
	if (Root == nullptr) return -1;
	auto current = Root;

	int size = value.size();
	int id = 0;
	while (current != nullptr && current->Value.size() >= size && current->Value != value)
	{
		current = current->Next;
		id++;
	}

	if (current != nullptr && current->Value == value)
		return id;

	return -1;
}

Node* SortedLinkedList::GetRoot()
{
	return Root;
}
