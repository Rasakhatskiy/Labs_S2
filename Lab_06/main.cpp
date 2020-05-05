#include "SortedLinkedList.hpp"
#include "SortedArrayList.hpp"
#include "SortedBinarySearchTree.hpp"

#include <iostream>

int main()
{
	/*SortedLinkedList list;
	list.Insert("Denis");
	list.Insert("ya");
	list.Insert("otsortiroval");
	list.Insert("etot");
	list.Insert("spisok");
	list.Insert("po");
	list.Insert("ubivaniy");
	list.Insert("dliny");

	int count = 0;
	for (auto i = list.GetRoot(); i != nullptr; i = i->Next)
		std::cout << "[" << count++ << "]" + i->Value << std::endl;

	std::cout << list.Search("etot") << std::endl;
	std::cout << list.Search("null") << std::endl;
	std::cout << list.Search("po") << std::endl;
	std::cout << list.Search("Denis") << std::endl;*/

	/*SortedArrayList list;
	list.Insert("Denis");
	list.Insert("ya");
	list.Insert("otsortiroval");
	list.Insert("etot");
	list.Insert("spisok");
	list.Insert("po");
	list.Insert("ubivaniy");
	list.Insert("dliny");

	int count = 0;
	for (auto i = list.Begin(); i != list.End(); i++)
		std::cout << "[" << count++ << "]"  << *i << std::endl;

	std::cout << list.Search("etot") << std::endl;
	std::cout << list.Search("null") << std::endl;
	std::cout << list.Search("po") << std::endl;
	std::cout << list.Search("Denis") << std::endl;*/

	SortedBinarySearchTree list;
	list.Insert("Denis");
	list.Insert("ya");
	list.Insert("otsortiroval");
	list.Insert("etot");
	list.Insert("spisok");
	list.Insert("po");
	list.Insert("ubivaniy");
	list.Insert("dliny");

	list.Remove("spisok");

	auto vec = list.ToVectorValues();
	for (auto& i : vec)
		std::cout << i << std::endl;


	std::cout << list.Search("etot")->Value << std::endl;
	std::cout << list.Search("null")->Value << std::endl;
	std::cout << list.Search("po")->Value << std::endl;
	std::cout << list.Search("Denis")->Value << std::endl;

}