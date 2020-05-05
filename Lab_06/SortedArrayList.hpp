#ifndef SORTED_ARRAY_LIST_HPP
#define SORTED_ARRAY_LIST_HPP
#include <vector>
#include <string>
#include <algorithm>

class SortedArrayList
{
	std::vector<std::string> Array;
public:
	void Insert(std::string value);
	void Remove(std::string value);
	void Remove(int id);
	int GetSize();
	int Search(std::string value);
	std::vector<std::string>::iterator Begin();
	std::vector<std::string>::iterator End();
	SortedArrayList();
	~SortedArrayList();
};


#endif // !SORTED_ARRAY_LIST_HPP


