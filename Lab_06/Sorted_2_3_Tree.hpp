#ifndef SORTED_2_3_TREE_HPP
#define SORTED_2_3_TREE_HPP

#include <string>
#include <algorithm>
#include <vector>

#include "ArrangedList.hpp"

typedef unsigned char byte;

class Sorted_2_3_Tree : public ArrangedList
{
	class Node
	{
	public:
		std::string Value_1;
		std::string Value_2;

		Node* Left;
		Node* Middle;
		Node* Right;

		Node* Parent;

		byte Values;

		Node(std::string value);
		Node(std::string value_1, std::string value_2);
		Node(std::string value, Node* left, Node* middle, Node* right, Node* parent);
		bool HasValue(std::string value);
		void Sort();
		void Insert(std::string value);
		void Remove(std::string value);
		void Join(std::string value, Node* first, Node* second);
		bool IsLeaf();
	};

	enum Rotation
	{
		None,
		Right,
		Left
	};


	void Dispose(Node* targetNode);
	Sorted_2_3_Tree::Node* Split(Node* targetNode);
	Node* Insert(Node* node, std::string value);
	Sorted_2_3_Tree::Node* Search(Node* targetNode, std::string value);
	Sorted_2_3_Tree::Node* Min(Node* targetNode);
	Sorted_2_3_Tree::Node* Remove(Node* targetNode, std::string value);
	Sorted_2_3_Tree::Node* Fix(Node* leaf);
	Sorted_2_3_Tree::Node* Redistribute(Node* leaf);
	Sorted_2_3_Tree::Node* Merge(Node* leaf);
	void ToVectorValues(Node* node, std::vector<std::string>& vector);

public:
	Sorted_2_3_Tree();
	~Sorted_2_3_Tree();
	Node* Root;

	void Insert(std::string value);
	void Remove(std::string value);
	bool Search(std::string value);

	std::vector<std::string> ToVectorValues();
	std::vector<Node *>		 ToVectorNodes();

};



#endif // !SORTED_2_3_TREE_HPP

