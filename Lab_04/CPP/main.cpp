#include <iostream>
#include "../Include/TreeInt.hpp"

int main()
{
	BinaryTree bintree;
	
	std::string pi = "314159265358979323846264338327950288419716939937510582097494459230";

	for (auto& i : pi) bintree.AddNode(i - '0');

	std::cout << bintree.ToString() << std::endl;

	auto bindata = bintree.GetData();

	for (auto& i : bindata) std::cout << std::to_string(i) + " ";
}