#include "SortedArrayList.hpp"



SortedArrayList::SortedArrayList()
{
}


SortedArrayList::~SortedArrayList()
{
}

void SortedArrayList::Insert(std::string value)
{
	int size = value.size();
	for (auto i = Array.begin(); i != Array.end(); ++i)
	{
		if (i->size() < size)
		{
			Array.insert(i, value);
			return;
		}
	}
	Array.insert(Array.end(), value);
}

void SortedArrayList::Remove(std::string value)
{
	Array.erase(std::remove(Array.begin(), Array.end(), value), Array.end());
}

void SortedArrayList::Remove(int id)
{
	Array.erase(Array.begin() + id);
}

int SortedArrayList::GetSize()
{
	return Array.size();
}

bool SortedArrayList::Search(std::string value)
{
	auto it = std::find(Array.begin(), Array.end(), value);
	if (it == Array.end()) 
		return false;
	return true;
}

std::vector<std::string> SortedArrayList::ToVectorValues()
{
	return Array;
}

std::vector<std::string>::iterator SortedArrayList::Begin()
{
	return Array.begin();
}

std::vector<std::string>::iterator SortedArrayList::End()
{
	return Array.end();
}
