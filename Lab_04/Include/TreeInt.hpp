#ifndef TREE_INT_HPP
#define TREE_INT_HPP

#include <vector>
#include <string>
#include <random>
#include <chrono>

class Tree
{
public:
	class Node 
	{
	public :
		long Value;

		Node* Parent;
		std::vector<Node*> Children;

		Node(Node* parent, long value);
		std::string ToString(std::string spacing, bool closing, bool root);

	private:
		static const unsigned char LineClosed = 192;
		static const unsigned char LineOpened = 195;
		static const unsigned char LineVertical = 179;
		static const unsigned char LineHorizontal = 196;
	};

	Node* Root;

	void AddNode(Node* &addTo, long value, float chance);
	std::string ToString();
	void DeleteNode(long value);

	Tree();
	~Tree();


private:
	void DeleteNode(Node* node);
	void DeleteNode(Node* node, long value);

	std::default_random_engine RandomEngine;
	std::uniform_int_distribution<int> RandomGenerator;
};

class BinaryTree
{
public:
	class Node
	{
	public:
		long Value;

		Node* Parent;
		Node* Left;
		Node* Right;

		Node(Node* parent, long value);
		std::string ToString(std::string spacing, bool closing, bool root);

	private:
		static const unsigned char LineClosed = 192;
		static const unsigned char LineOpened = 195;
		static const unsigned char LineVertical = 179;
		static const unsigned char LineHorizontal = 196;
	};

	Node* Root;

	void AddNode(long value);
	std::string ToString();

	BinaryTree();
	~BinaryTree();

private:
	void DeleteNode(Node* node);
	void AddNode(Node*& node, long value);
};

#endif

