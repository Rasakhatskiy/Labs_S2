#include "../Include/TreeInt.hpp"



Tree::Tree() : 
	Root(nullptr), 
	RandomGenerator(std::uniform_int_distribution<int>{ 1, 100 }){}

Tree::~Tree()
{
	DeleteNode(Root);
}


std::string Tree::ToString()
{
	return Root->ToString("", true, true);
}

void Tree::AddNode(Node* &addTo, long value, float chance)
{
	//if no node, create and assign value
	//if no children, create one and assign value
	//with chance create new child or random grandchild

	if (!addTo)
	{
		addTo = new Node(nullptr, value);
		return;
	}

	bool flag = (RandomGenerator(RandomEngine) / 100.0) <= chance;
	if (flag || addTo->Children.size() == 0)
	{
		addTo->Children.push_back(new Node(addTo, value));
	}
	else
	{
		std::uniform_int_distribution<int> RandomChildren{ 0, int(addTo->Children.size() - 1) };
		Node* child = addTo->Children[RandomChildren(RandomEngine)];
		AddNode(child, value, 1);
	}
}

void Tree::DeleteNode(long value)
{
	DeleteNode(Root, value);
}

void Tree::DeleteNode(Node* node)
{
	if (node == nullptr) return;

	for (auto& i : node->Children)
		DeleteNode(i);

	node->Children.clear();

	delete node;
}


void Tree::DeleteNode(Node* node, long value)
{
	if (!node) return;

	if (node->Value == value)
	{
		if (node->Parent)
			for (int i = 0; i < node->Parent->Children.size(); i++)
				if (node->Parent->Children[i] == node)
					node->Parent->Children.erase(node->Parent->Children.begin() + i);


		DeleteNode(node);
		return;
	}
	else
	{
		for (auto& i : node->Children) 
			DeleteNode(i, value);
	}
}

Tree::Node::Node(Tree::Node* parent, long value) :
	Parent(parent), Value(value) {}

std::string Tree::Node::ToString(std::string spacing, bool closing, bool root = false)
{
	std::string result = spacing;
	if (closing)
	{
		if (!root)
		{
			result += LineClosed;
			spacing += "  ";
		}
	}
	else
	{
		result += LineOpened;
		spacing += LineVertical;
		spacing += " ";
	}

	if (!root) result += LineHorizontal;
	result += std::to_string(Value) + "\n";

	for (int i = 0; i < Children.size(); i++)
		result += (Children[i])->ToString(spacing, (i == Children.size() - 1));

	return result;
}

//================================================================================================

BinaryTree::BinaryTree():
	Root(nullptr){}

BinaryTree::~BinaryTree()
{
	DeleteNode(Root);
}


std::string BinaryTree::ToString()
{
	return Root->ToString("", true, true);
}

void BinaryTree::AddNode(long value)
{
	AddNode(Root, value);
}

void BinaryTree::AddNode(BinaryTree::Node* &node, long value)
{
	if (!node)
	{
		node = new Node(nullptr, value);
		return;
	}

	if (value < node->Value)
		AddNode(node->Left, value);
	else
		AddNode(node->Right, value);
}

void BinaryTree::DeleteNode(BinaryTree::Node* node)
{
	if (node == nullptr) return;
	DeleteNode(node->Left);
	DeleteNode(node->Right);
	delete node;
}

std::vector<long> BinaryTree::GetData()
{
	return GetData(Root);
}

std::vector<long> BinaryTree::GetData(BinaryTree::Node* node)
{
	std::vector<long> result;
	if (!node) return result;
	result.push_back(node->Value);

	std::vector<long> left = GetData(node->Left);
	std::vector<long> right = GetData(node->Right);

	result.insert(result.end(), left.begin(), left.end());
	result.insert(result.end(), right.begin(), right.end());

	return result;
}


BinaryTree::Node::Node(Node* parent, long value) :
	Parent(parent), Value(value) {}

std::string BinaryTree::Node::ToString(std::string spacing, bool closing, bool root = false)
{
	std::string result = spacing;
	if (closing)
	{
		if (!root)
		{
			result += LineClosed;
			spacing += "  ";
		}
	}
	else
	{
		result += LineOpened;
		spacing += LineVertical;
		spacing += " ";
	}

	if (!root) result += LineHorizontal;
	result += std::to_string(Value) + "\n";

	if(Left) result += Left->ToString(spacing, !Right);
	if(Right) result += Right->ToString(spacing, true);
	
	return result;
}
