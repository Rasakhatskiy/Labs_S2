#include "SortedAvlTree.hpp"

SortedAvlTree::Node::Node() :
	Left(nullptr), Right(nullptr), Height(NULL), Value("") {}

SortedAvlTree::Node::Node(std::string value) :
	Left(nullptr), Right(nullptr), Height(NULL), Value(value) {}

SortedAvlTree::SortedAvlTree():
	Root(nullptr), Size(0) {}

SortedAvlTree::~SortedAvlTree(){}

void SortedAvlTree::Insert(std::string value)
{
	Root = Insert(value, Root);
}

void SortedAvlTree::Remove(std::string value)
{
	Remove(value, Root);
}

bool SortedAvlTree::Search(std::string value)
{
	return Search(value, Root);
}

int SortedAvlTree::GetSize()
{
	return Size;
}

std::vector<std::string> SortedAvlTree::ToVectorValues()
{
	std::vector <std::string> vector;
	PushToVector(vector, Root);
	return vector;
}

std::vector<SortedAvlTree::Node*> SortedAvlTree::ToVectorNodes()
{
	std::vector <Node*> vector;
	PushToVector(vector, Root);
	return vector;
}



int SortedAvlTree::Height(Node* targetNode)
{
	if (!targetNode)
		return 0;
	else
		return targetNode->Height;
}

int SortedAvlTree::Balance(Node* targetNode)
{
	if (targetNode == nullptr)
		return 0;
	else
		return Height(targetNode->Left) - Height(targetNode->Right);
}


SortedAvlTree::Node* SortedAvlTree::GetMinValNode(Node* targetNode)
{
	Node* current = targetNode;
	while (current->Left != nullptr)
		current = current->Left;
	return current;
}

SortedAvlTree::Node* SortedAvlTree::RotateRight(Node* targetNode)
{
	Node* left = targetNode->Left;
	Node* temp = left->Right;

	left->Right = targetNode;
	targetNode->Left = temp;

	targetNode->Height = std::max(Height(targetNode->Left),Height(targetNode->Right)) + 1;
	left->Height = std::max(Height(left->Left),Height(left->Right)) + 1;
	return left;
}

SortedAvlTree::Node* SortedAvlTree::RotateLeft(Node* targetNode)
{
	Node* right = targetNode->Right;
	Node* T2 = right->Left;

	right->Left = targetNode;
	targetNode->Right = T2;

	targetNode->Height = std::max(Height(targetNode->Left), Height(targetNode->Right)) + 1;
	right->Height = std::max(Height(right->Left), Height(right->Right)) + 1;

	return right;
}


SortedAvlTree::Node* SortedAvlTree::Insert(std::string value, Node* targetNode)
{
	if (!targetNode)
	{
		Size++;
		targetNode = new Node(value);
		return targetNode;
	}

	if (targetNode->Value.size() > value.size())
		targetNode->Left = Insert(value, targetNode->Left);
	else if (targetNode->Value.size() <= value.size())
		targetNode->Right = Insert(value, targetNode->Right);
	else  
		return targetNode;


	targetNode->Height = std::max(Height(targetNode->Left), Height(targetNode->Right)) + 1;

	int balance = Balance(targetNode);

	if (balance > 1 && value.size() < targetNode->Left->Value.size())
	{
		return RotateRight(targetNode);
	}

	if (balance < -1 && value.size() > targetNode->Right->Value.size())
	{
		return RotateLeft(targetNode);
	}

	if (balance > 1 && value.size() > targetNode->Left->Value.size())
	{
		targetNode->Left = RotateLeft(targetNode->Left);
		return RotateRight(targetNode);
	}

	if (balance < -1 && value.size() < targetNode->Right->Value.size())
	{
		targetNode->Right = RotateRight(targetNode->Right);
		return RotateLeft(targetNode);
	}

	return targetNode;
}

SortedAvlTree::Node* SortedAvlTree::Remove(std::string value, Node* targetNode)
{
	if (!targetNode)
	{
		return nullptr;
	}
	else if (targetNode->Value.size() > value.size())
	{
		targetNode->Left = Remove(value, targetNode->Left);
	}
	else if (targetNode->Value.size() < value.size())
	{
		targetNode->Right = Remove(value, targetNode->Right);
	}
	else if (targetNode->Value.size() == value.size() && targetNode->Value != value)
	{
		targetNode->Right = Remove(value, targetNode->Right);
	}
	else if(targetNode->Value.size() == value.size())
	{
		if (!targetNode->Left || !targetNode->Right)
		{
			Node* temp = 
				targetNode->Left ?
				targetNode->Left :
				targetNode->Right;

			if (!temp)
			{
				temp = targetNode;
				targetNode = nullptr;
			}
			else
			{
				*targetNode = *temp;
			}
			free(temp);
		}
		else
		{
			Node* temp = GetMinValNode(targetNode->Right);
			targetNode->Value = temp->Value;
			targetNode->Right = Remove(temp->Value, targetNode->Right);
		}
	}

	if (!targetNode)
	{
		return nullptr;
	}
	else
	{
		targetNode->Height = std::max(Height(targetNode->Left), Height(targetNode->Right)) + 1;

		int balance = Balance(targetNode);

		if (balance > 1 && Balance(targetNode->Left) >= 0)
		{
			return RotateRight(targetNode);
		}
		else if (balance > 1 && Balance(targetNode->Left) < 0)
		{
			targetNode->Left = RotateLeft(targetNode->Left);
			return RotateRight(targetNode);
		}
		else if (balance < -1 && Balance(targetNode->Right) <= 0)
		{
			return RotateLeft(targetNode);
		}
		else if (balance < -1 && Balance(targetNode->Right) > 0)
		{
			targetNode->Right = RotateRight(targetNode->Right);
			return RotateLeft(targetNode);
		}
		else
		{
			return targetNode;
		}
	}
}

SortedAvlTree::Node* SortedAvlTree::Search(std::string value, Node* targetNode)
{
	if (!targetNode)
	{
		return nullptr;
	}
	else if (targetNode->Value.size() == value.size())
	{
		if(targetNode->Value != value)
			return Search(value, targetNode->Right);
		else
			return targetNode;
	}
	else if (targetNode->Value.size() > value.size())
	{
		return Search(value, targetNode->Left);
	}
	else
	{
		return Search(value, targetNode->Right);
	}
}


void SortedAvlTree::PushToVector(std::vector<std::string>& vector, Node* targetNode)
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

void SortedAvlTree::PushToVector(std::vector<SortedAvlTree::Node*>& vector, Node* targetNode)
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
