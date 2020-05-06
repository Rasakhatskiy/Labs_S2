#include "SortedBinarySearchTree.hpp"

SortedBinarySearchTree::Node::Node() :
	Left(nullptr), Right(nullptr), Value("") {}

SortedBinarySearchTree::Node::Node(std::string value) :
	Left(nullptr), Right(nullptr), Value(value) {}



SortedBinarySearchTree::SortedBinarySearchTree() :
	Root(nullptr), Size(0) {}

SortedBinarySearchTree::~SortedBinarySearchTree()
{
}



void SortedBinarySearchTree::Insert(std::string value)
{
	Insert(value, Root);
}

void SortedBinarySearchTree::Insert(std::string value, Node*&targetNode)
{
	if (!targetNode)
	{
		targetNode = new Node(value);
		Size++;
	}
	else if (targetNode->Value.size() > value.size())
	{
		Insert(value, targetNode->Left);
	}
	else
	{
		Insert(value, targetNode->Right);
	}
}


 
SortedBinarySearchTree::Node* SortedBinarySearchTree::Remove(std::string value, Node* &targetNode)
{
	if (targetNode == nullptr)
	{
		return nullptr;
	}
	if (targetNode->Value.size() > value.size())
	{
		targetNode->Left = Remove(value, targetNode->Left);
		return targetNode;
	}
	else if (targetNode->Value.size() < value.size())
	{
		targetNode->Right = Remove(value, targetNode->Right);
		return targetNode;
	}
	else
	{
		if (!targetNode->Left)
		{
			auto temp = targetNode->Right;
			free(targetNode);
			return temp;
		}
		else if (!targetNode->Right)
		{
			auto temp = targetNode->Left;
			free(targetNode);
			return temp;
		}
		else
		{
			auto temp = MinValue(targetNode->Right);
			targetNode->Value = temp->Value;
			targetNode->Right = Remove(temp->Value, targetNode->Right);
			targetNode->Right = nullptr;
			return targetNode;
		}
	}
}

SortedBinarySearchTree::Node* SortedBinarySearchTree::MinValue(Node* targetNode)
{
	while (targetNode->Left)
		targetNode = targetNode->Left;
	return targetNode;
}



void SortedBinarySearchTree::Remove(std::string value)
{
	Remove(value, Root);
}

int SortedBinarySearchTree::GetSize()
{
	return Size;
}

bool SortedBinarySearchTree::Search(std::string value)
{
	return Search(value, Root);
}

SortedBinarySearchTree::Node* SortedBinarySearchTree::Search(std::string value, Node* targetNode)
{
	if (!targetNode)
	{
		return nullptr;
	}
	else if (targetNode->Value == value)
	{
		return targetNode;
	}
	else if(targetNode->Value.size() > value.size())
	{
		return Search(value, targetNode->Left);
	}
	else
	{
		return Search(value, targetNode->Right);
	}
}



std::vector<std::string> SortedBinarySearchTree::ToVectorValues()
{
	std::vector <std::string> vector;
	PushToVector(vector, Root);
	return vector;
}

std::vector<SortedBinarySearchTree::Node*> SortedBinarySearchTree::ToVectorNodes()
{
	std::vector <Node*> vector;
	PushToVector(vector, Root);
	return vector;
}

void SortedBinarySearchTree::PushToVector(std::vector<std::string> &vector, Node* targetNode)
{
	if (!targetNode)
	{
		return;
	}
	else
	{
		PushToVector(vector, targetNode->Right);
		vector.push_back(targetNode->Value);
		PushToVector(vector, targetNode->Left);
	}
}

void SortedBinarySearchTree::PushToVector(std::vector<SortedBinarySearchTree::Node*>& vector, Node* targetNode)
{
	if (!targetNode)
	{
		return;
	}
	else
	{
		PushToVector(vector, targetNode->Right);
		vector.push_back(targetNode);
		PushToVector(vector, targetNode->Left);
	}
}