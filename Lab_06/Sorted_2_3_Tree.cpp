#include "Sorted_2_3_Tree.hpp"
typedef unsigned char byte;

Sorted_2_3_Tree::Sorted_2_3_Tree() :
	Root(nullptr) {}

Sorted_2_3_Tree::~Sorted_2_3_Tree()
{
	Dispose(Root);
}

void Sorted_2_3_Tree::Insert(std::string value)
{
	Insert(Root, value);
}

void Sorted_2_3_Tree::Remove(std::string value)
{
	Remove(Root, value);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Search(std::string value)
{
	return Search(Root, value);
}



void Sorted_2_3_Tree::Dispose(Node* targetNode)
{
	if (!targetNode) return;
	Dispose(targetNode->Left);
	Dispose(targetNode->Middle);
	Dispose(targetNode->Right);
	delete targetNode;
}

Sorted_2_3_Tree::Node::Node(std::string value) :
	Left(nullptr), Middle(nullptr), Right(nullptr), 
	Value_1(value), Value_2(std::string()), Values(1) {}

Sorted_2_3_Tree::Node::Node(std::string value_1, std::string value_2) :
	Left(nullptr), Middle(nullptr), Right(nullptr),
	Value_1(value_1), Value_2(value_2), Values(2) {}

Sorted_2_3_Tree::Node::Node(std::string value, Node* left, Node* middle, Node* right, Node* parent) :
	Values(1), Value_1(value), Value_2(std::string()), 
	Left(left), Middle(middle), Right(right), 
	Parent(parent) {}


bool Sorted_2_3_Tree::Node::HasValue(std::string value)
{
	return Value_1 == value || Value_2 == value;
}

void Sorted_2_3_Tree::Node::Sort()
{
	if (Values <= 1) 
		return;
	if (Value_1.size() > Value_2.size())
		std::swap(Value_1, Value_2);
}

void Sorted_2_3_Tree::Node::Insert(std::string value)
{
	if (Values == 0) Value_1 = value;
	if (Values == 1) Value_2 = value;
	Values++;
	Sort();
}

void Sorted_2_3_Tree::Node::Remove(std::string value)
{
	if (Values == 1 && Value_1 == value)
	{
		Value_1 = Value_2;
		Values--;
	}
	if (Values == 2 && Value_2 == value) 
	{
		Value_2 = std::string();
		Values--;
	}
}

void Sorted_2_3_Tree::Node::Join(std::string value, Node * first, Node * second)
{
	Value_1 = value;
	Value_2 = std::string();

	Left = first;
	Middle = second;
	Right = nullptr;

	Values = 1;
}

bool Sorted_2_3_Tree::Node::IsLeaf() 
{
	return !Left && !Middle && !Right;
}



Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Split(Node* targetNode) 
{
	if (targetNode->Values < 2) return targetNode;

	auto one = new Node(
		targetNode->Value_1, 
		targetNode->Left, 
		targetNode->Middle, 
		nullptr, 
		targetNode->Parent);

	auto two = new Node(
		targetNode->Value_2, 
		targetNode->Right, 
		nullptr, 
		nullptr, 
		targetNode->Parent);
	

	if (one->Left)  
		one->Left->Parent = one;

	if (one->Middle) 
		one->Middle->Parent = one;

	if (two->Left)  
		two->Left->Parent = two;

	if (two->Middle)
		two->Middle->Parent = two;


	if (targetNode->Parent) 
	{
		targetNode->Parent->Insert(targetNode->Value_2);

		if (targetNode->Parent->Left == targetNode) targetNode->Parent->Left = nullptr;
		else if (targetNode->Parent->Middle == targetNode) targetNode->Parent->Middle = nullptr;
		else if (targetNode->Parent->Right == targetNode) targetNode->Parent->Right = nullptr;

		if (!targetNode->Parent->Left) 
		{
			targetNode->Parent->Right = targetNode->Parent->Middle;
			targetNode->Parent->Middle = two;
			targetNode->Parent->Left = one;
		}
		else if (targetNode->Parent->Middle == nullptr) 
		{
			targetNode->Parent->Right = two;
			targetNode->Parent->Middle = one;
		}
		else 
		{
			targetNode->Parent->Right = one;
		}

		Node* temp = targetNode->Parent;
		delete targetNode;
		return temp;
	}
	else 
	{
		one->Parent = targetNode;
		two->Parent = targetNode;
		targetNode->Join(targetNode->Value_2, one, two);
		return targetNode;
	}
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Insert(Node* node, std::string value)
{
	if (!node) 
		return new Node(value);
	else if (node->IsLeaf()) 
		node->Insert(value);
	else if (value.size() <= node->Value_1.size()) 
		Insert(node->Left, value);
	else if ((node->Values == 1) || ((node->Values == 2) && value.size() <= node->Value_2.size()))
		Insert(node->Middle, value);
	else 
		Insert(node->Right, value);

	return Split(node);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Search(Node* targetNode, std::string value) 
{
	if (!targetNode) return nullptr;

	if (targetNode->HasValue(value)) 
		return targetNode;
	else if (value < targetNode->Value_1) 
		return Search(targetNode->Left, value);
	else if ((targetNode->Values == 2) && (value.size() < targetNode->Value_2.size()) || (targetNode->Values == 1)) 
		return Search(targetNode->Middle, value);
	else if (targetNode->Values == 2) 
		return Search(targetNode->Right, value);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Min(Node* targetNode) 
{
	if (!targetNode) return targetNode;
	if (!(targetNode->Left)) return targetNode;
	else return Min(targetNode->Left);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Remove(Node* targetNode, std::string value) 
{
	auto item = Search(targetNode, value);

	if (!item) return targetNode;

	Node* min = nullptr;

	if (item->Value_1.size() == value.size()) 
		min = Min(item->Middle);
	else 
		min = Min(item->Right);

	if (min) 
	{ 
		std::string &z = (
			value == item->Value_1 ? 
			item->Value_1 : 
			item->Value_2);

		std::swap(z, min->Value_1);
		item = min;
	}

	item->Remove(value);

	return Fix(item);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Fix(Node* leaf)
{
	if (!leaf->Values && !leaf->Parent) 
	{
		delete leaf;
		return nullptr;
	}
	if (leaf->Values)
	{
		if (leaf->Parent) return Fix(leaf->Parent);
		else return leaf;
	}

	auto parent = leaf->Parent;
	if (parent->Left->Values == 2 || parent->Middle->Values == 2 || parent->Values == 2)
		leaf = Redistribute(leaf);
	else if (parent->Values == 2 && parent->Right->Values == 2)
		leaf = Redistribute(leaf);
	else leaf = Merge(leaf);

	return Fix(leaf);
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Redistribute(Node* leaf) {
	auto parent = leaf->Parent;
	auto first = parent->Left;
	auto second = parent->Middle;
	auto third = parent->Right;

	if ((parent->Values == 2) && (first->Values < 2) && (second->Values < 2) && (third->Values < 2)) 
	{
		if (first == leaf) 
		{
			parent->Left = parent->Middle;
			parent->Middle = parent->Right;
			parent->Right = nullptr;
			parent->Left->Insert(parent->Value_1);
			parent->Left->Right = parent->Left->Middle;
			parent->Left->Middle = parent->Left->Left;

			if (leaf->Left != nullptr) 
				parent->Left->Left = leaf->Left;
			else if (leaf->Middle != nullptr) 
				parent->Left->Left = leaf->Middle;

			if (parent->Left->Left != nullptr)
				parent->Left->Left->Parent = parent->Left;

			parent->Remove(parent->Value_1);
			delete first;
		}
		else if (second == leaf) 
		{
			first->Insert(parent->Value_1);
			parent->Remove(parent->Value_1);

			if (leaf->Left != nullptr) 
				first->Right = leaf->Left;
			else if (leaf->Middle != nullptr) 
				first->Right = leaf->Middle;

			if (first->Right != nullptr) 
				first->Right->Parent = first;

			parent->Middle = parent->Right;
			parent->Right = nullptr;

			delete second;
		}
		else if (third == leaf) 
		{
			second->Insert(parent->Value_2);
			parent->Right = nullptr;
			parent->Remove(parent->Value_2);

			if (leaf->Left != nullptr) 
				second->Right = leaf->Left;
			else if (leaf->Middle != nullptr) 
				second->Right = leaf->Middle;

			if (second->Right != nullptr)  
				second->Right->Parent = second;

			delete third;
		}
	}
	else if ((parent->Values == 2) && ((first->Values == 2) || (second->Values == 2) || (third->Values == 2))) 
	{
		if (third == leaf)
		{
			if (leaf->Left != nullptr) 
			{
				leaf->Middle = leaf->Left;
				leaf->Left = nullptr;
			}

			leaf->Insert(parent->Value_2);

			if (second->Values == 2) 
			{
				parent->Value_2 = second->Value_2;
				second->Remove(second->Value_2);
				leaf->Left = second->Right;
				second->Right = nullptr;

				if (leaf->Left != nullptr) 
					leaf->Left->Parent = leaf;
			}
			else if (first->Values == 2)
			{
				parent->Value_2 = second->Value_1;
				leaf->Left = second->Middle;
				second->Middle = second->Left;

				if (leaf->Left != nullptr) 
					leaf->Left->Parent = leaf;

				second->Value_1 = parent->Value_1;
				parent->Value_1 = first->Value_2;
				first->Remove(first->Value_2);
				second->Left = first->Right;

				if (second->Left != nullptr) 
					second->Left->Parent = second;

				first->Right = nullptr;
			}
		}
		else if (second == leaf) 
		{
			if (third->Values == 2)
			{
				if (leaf->Left == nullptr)
				{
					leaf->Left = leaf->Middle;
					leaf->Middle = nullptr;
				}

				second->Insert(parent->Value_2);
				parent->Value_2 = third->Value_1;
				third->Remove(third->Value_1);
				second->Middle = third->Left;

				if (second->Middle != nullptr) 
					second->Middle->Parent = second;

				third->Left = third->Middle;
				third->Middle = third->Right;
				third->Right = nullptr;
			}
			else if (first->Values == 2) 
			{
				if (leaf->Middle == nullptr) 
				{
					leaf->Middle = leaf->Left;
					leaf->Left = nullptr;
				}
				second->Insert(parent->Value_1);
				parent->Value_1 = first->Value_2;
				first->Remove(first->Value_2);
				second->Left = first->Right;

				if (second->Left != nullptr) 
					second->Left->Parent = second;

				first->Right = nullptr;
			}
		}
		else if (first == leaf)
		{
			if (leaf->Left == nullptr) 
			{
				leaf->Left = leaf->Middle;
				leaf->Middle = nullptr;
			}
			first->Insert(parent->Value_1);
			if (second->Values == 2)
			{
				parent->Value_1 = second->Value_1;
				second->Remove(second->Value_1);
				first->Middle = second->Left;

				if (first->Middle != nullptr)
					first->Middle->Parent = first;

				second->Left = second->Middle;
				second->Middle = second->Right;
				second->Right = nullptr;
			}
			else if (third->Values == 2) 
			{
				parent->Value_1 = second->Value_1;
				second->Value_1 = parent->Value_2;
				parent->Value_2 = third->Value_1;
				third->Remove(third->Value_1);
				first->Middle = second->Left;

				if (first->Middle != nullptr) 
					first->Middle->Parent = first;

				second->Left = second->Middle;
				second->Middle = third->Left;

				if (second->Middle != nullptr) 
					second->Middle->Parent = second;

				third->Left = third->Middle;
				third->Middle = third->Right;
				third->Right = nullptr;
			}
		}
	}
	else if (parent->Values == 1) 
{
		leaf->Insert(parent->Value_1);

		if (first == leaf && second->Values == 2) 
		{
			parent->Value_1 = second->Value_1;
			second->Remove(second->Value_1);

			if (leaf->Left == nullptr) 
				leaf->Left = leaf->Middle;

			leaf->Middle = second->Left;
			second->Left = second->Middle;
			second->Middle = second->Right;
			second->Right = nullptr;

			if (leaf->Middle != nullptr)
				leaf->Middle->Parent = leaf;
		}
		else if (second == leaf && first->Values == 2)
		{
			parent->Value_1 = first->Value_2;
			first->Remove(first->Value_2);

			if (leaf->Middle == nullptr)
				leaf->Middle = leaf->Left;

			leaf->Left = first->Right;
			first->Right = nullptr;

			if (leaf->Left != nullptr) 
				leaf->Left->Parent = leaf;
		}
	}
	return parent;
}

Sorted_2_3_Tree::Node* Sorted_2_3_Tree::Merge(Node* leaf) {
	auto parent = leaf->Parent;

	if (parent->Left == leaf) 
	{
		parent->Middle->Insert(parent->Value_1);
		parent->Middle->Right = parent->Middle->Middle;
		parent->Middle->Middle = parent->Middle->Left;

		if (leaf->Left != nullptr) 
			parent->Middle->Left = leaf->Left;
		else if (leaf->Middle != nullptr)
			parent->Middle->Left = leaf->Middle;

		if (parent->Middle->Left != nullptr) 
			parent->Middle->Left->Parent = parent->Middle;

		parent->Remove(parent->Value_1);
		delete parent->Left;
		parent->Left = nullptr;
	}
	else if (parent->Middle == leaf) {
		parent->Left->Insert(parent->Value_1);

		if (leaf->Left != nullptr)
			parent->Left->Right = leaf->Left;
		else if (leaf->Middle != nullptr) 
			parent->Left->Right = leaf->Middle;

		if (parent->Left->Right != nullptr)
			parent->Left->Right->Parent = parent->Left;

		parent->Remove(parent->Value_1);
		delete parent->Middle;
		parent->Middle = nullptr;
	}

	if (parent->Parent == nullptr) 
	{
		Node* tmp = nullptr;

		if (parent->Left != nullptr)
			tmp = parent->Left;
		else tmp = parent->Middle;

		tmp->Parent = nullptr;
		delete parent;
		return tmp;
	}
	return parent;
}


