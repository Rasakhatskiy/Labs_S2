#include <iostream>
#include "../Include/TreeInt.hpp"

int main()
{
	Tree tree;
	for (int i = 1; i < 100; i++)
	{
		tree.AddNode(tree.Root, i,  i / 100.0);
	}


	std::cout << tree.ToString() << std::endl;


	tree.DeleteNode(6);

	std::cout << tree.ToString() << std::endl;
}