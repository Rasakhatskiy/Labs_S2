#ifndef ARRANGED_LIST_HPP
#define ARRANGED_LIST_HPP

#include <string>
#include <vector>

class ArrangedList
{
public:
	ArrangedList() {};
	virtual ~ArrangedList() {};

	virtual void Insert(std::string value) { throw std::bad_exception(); };
	virtual void Remove(std::string value) { throw std::bad_exception(); };
	virtual bool Search(std::string value) { throw std::bad_exception(); };
	virtual std::vector<std::string> ToVectorValues() { throw std::bad_exception(); };
};

#endif