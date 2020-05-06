#ifndef SORTED_AVL_TREE_HPP
#define SORTED_AVL_TREE_HPP

#include <string>
#include <algorithm>
#include <vector>

#include "ArrangedList.hpp"

class SortedAvlTree : public ArrangedList
{
	struct Node
	{
		Node* Left;
		Node* Right;
		unsigned Height;
		std::string Value;
		Node(std::string value);
		Node();
	};


	int Height(Node* targetNode);
	int Balance(Node* N);
	Node* RotateLeft(Node* targetNode);
	Node* RotateRight(Node* targetNode);
	Node* GetMinValNode(Node* node);

	Node* Insert(std::string value, Node* targetNode);
	Node* Remove(std::string value, Node* targetNode);
	Node* Search(std::string value, Node* targetNode);

	void PushToVector(std::vector<std::string>& vector, Node* targetNode);
	void PushToVector(std::vector<Node*>& vector, Node* targetNode);

	int Size;
public:
	SortedAvlTree();
	~SortedAvlTree();

	Node* Root;

	int GetSize();

	void Insert(std::string value);
	void Remove(std::string value);
	bool Search(std::string value);
	std::vector<std::string> ToVectorValues();
	std::vector<SortedAvlTree::Node*> ToVectorNodes();

};
#endif // !SORTED_AVL_TREE_HPP

