#ifndef SORTED_BINARY_SEARCH_TREE_HPP
#define SORTED_BINARY_SEARCH_TREE_HPP

#include <string>
#include <vector>

class SortedBinarySearchTree
{
	struct Node
	{
		Node* Left;
		Node* Right;
		std::string Value;
		Node(std::string value);
		Node();
	};

	void Insert(std::string value, Node *&targetNode);
	Node* Remove(std::string value, Node* &targetNode);
	Node* MinValue(Node* targetNode);
	Node* Search(std::string value, Node* targetNode);
	void PushToVector(std::vector<std::string> &vector, Node* targetNode);
	void PushToVector(std::vector<Node*> &vector, Node* targetNode);
	int Size;
public:
	Node* Root;


	SortedBinarySearchTree();
	~SortedBinarySearchTree();

	void Insert(std::string value);
	void Remove(std::string value);
	int GetSize();
	Node* Search(std::string value);
	std::vector<std::string> ToVectorValues();
	std::vector<Node*> ToVectorNodes();
};
#endif // !SORTED_BINARY_SEARCH_TREE_HPP


