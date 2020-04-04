#include "LogicTree.hpp"


LogicTree::LogicTree(std::string problem)
{
	Root = SetProblem(problem);
	
}

LogicTree::~LogicTree()
{
	DeleteNode(Root);
}


std::string LogicTree::ToString()
{
	return Root->ToString("", true, true);
}

void LogicTree::AddNode(long value)
{
	AddNode(Root, value);
}

void LogicTree::AddNode(LogicTree::Node*& node, long value)
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

void LogicTree::DeleteNode(LogicTree::Node* node)
{
	if (node == nullptr) return;
	DeleteNode(node->Left);
	DeleteNode(node->Right);
	delete node;
}

std::vector<long> LogicTree::GetData()
{
	return GetData(Root);
}

std::vector<long> LogicTree::GetData(LogicTree::Node * node)
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


LogicTree::Node::Node(LogicTree::Node * parent, long value) :
	Parent(parent), Value(value) {}

std::string LogicTree::Node::ToString(std::string spacing, bool closing, bool root = false)
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

	if (Left) result += Left->ToString(spacing, !Right);
	if (Right) result += Right->ToString(spacing, true);

	return result;
}


bool LogicTree::IsOperator(char c)
{
	if (c == '&' || c == '|' || c == '!' ||
		c == '+' || c == '>' || c == '=')
		return true;
	return false;
}

bool LogicTree::IsOperand(char c)
{
	if (c >= '0' && c <= '9') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	return false;
}

LogicTree::Node * LogicTree::AddNode(int value)
{
	Node* node = new Node(nullptr, value);
	node->Left = node->Right = nullptr;
	return node;
};

LogicTree::Node* LogicTree::SetProblem(std::string problem)
{
	std::stack<Node*> stackNodes;
	Node* result, * t1, * t2;

	// Traverse through every character of 
	// input expression 
	for (int i = 0; i < problem.size(); i++)
	{
		// If operand, simply push into stack 
		if (!IsOperator(problem[i]))
		{
			result = AddNode(problem[i]);
			stackNodes.push(result);
		}
		else // operator 
		{
			result = AddNode(problem[i]);

			// Pop two top nodes 
			t1 = stackNodes.top(); // Store top 
			stackNodes.pop();      // Remove top 
			t2 = stackNodes.top();
			stackNodes.pop();

			//  make them children 
			result->Right = t1;
			result->Left = t2;

			// Add this subexpression to stack 
			stackNodes.push(result);
		}
	}

	//  only element will be root of expression 
	// tree 
	result = stackNodes.top();
	stackNodes.pop();

	return result;
}

std::string LogicTree::InfixToPostfix(std::string expression)
{
	// Declaring a Stack from Standard template library in C++. 
	std::stack<char> S;
	std::string postfix = ""; // Initialize postfix as empty string.
	for (int i = 0; i < expression.length(); i++) {

		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		if (expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if (IsOperator(expression[i]))
		{
			while (!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), expression[i]))
			{
				postfix += S.top();
				S.pop();
			}
			S.push(expression[i]);
		}
		// Else if character is an operand
		else if (IsOperand(expression[i]))
		{
			postfix += expression[i];
		}

		else if (expression[i] == '(')
		{
			S.push(expression[i]);
		}

		else if (expression[i] == ')')
		{
			while (!S.empty() && S.top() != '(') {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}

	while (!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}

int LogicTree::GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
		case '+':
		case '-':
			weight = 1;
		case '*':
		case '/':
			weight = 2;
		case '$':
			weight = 3;
	}
	return weight;
}

bool LogicTree::HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if (op1Weight == op2Weight)
		return true;

	return op1Weight > op2Weight ? true : false;
}