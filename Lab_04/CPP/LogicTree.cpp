#include "../Include/LogicTree.hpp"

LogicTree::LogicTree() :
	Root(nullptr){}

LogicTree::LogicTree(std::string problem)
{
	problem = InfixToPostfix(problem);
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
	result += Value;
	result += "\n";

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
	for (int i = 0; i < problem.size(); i++)
	{
		if (!IsOperator(problem[i]))
		{
			result = AddNode(problem[i]);
			stackNodes.push(result);
		}
		else
		{
			result = AddNode(problem[i]);
			t1 = stackNodes.top(); 
			stackNodes.pop();
			t2 = stackNodes.top();
			stackNodes.pop();
			result->Right = t1;
			result->Left = t2;
			stackNodes.push(result);
		}
	}
	result = stackNodes.top();
	stackNodes.pop();

	return result;
}

std::string LogicTree::InfixToPostfix(std::string expression)
{
	std::stack<char> stack;
	std::string postfix = "";
	for (int i = 0; i < expression.length(); i++) 
	{
		if (expression[i] == ' ' || expression[i] == ',') continue;
		else if (IsOperator(expression[i]))
		{
			while (!stack.empty() && stack.top() != '(' && HasHigherPrecedence(stack.top(), expression[i]))
			{
				postfix += stack.top();
				stack.pop();
			}
			stack.push(expression[i]);
		}
		else if (IsOperand(expression[i]))
		{
			postfix += expression[i];
		}
		else if (expression[i] == '(')
		{
			stack.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			while (!stack.empty() && stack.top() != '(') 
			{
				postfix += stack.top();
				stack.pop();
			}
			stack.pop();
		}
	}

	while (!stack.empty()) {
		postfix += stack.top();
		stack.pop();
	}

	return postfix;
}

int LogicTree::GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
		case '=': weight = 1; break;
		case '>': weight = 2; break;
		case '|':
		case '+': weight = 3; break;
		case '&': weight = 4; break;
			break;
	}
	return weight;
}

bool LogicTree::HasHigherPrecedence(char op1, char op2)
{
	return GetOperatorWeight(op1) >= GetOperatorWeight(op2);
}

bool LogicTree::Solve()
{
	return Solve(Root);
}

bool LogicTree::Solve(LogicTree::Node* node)
{
	if (node->Left == nullptr || node->Right == nullptr)
	{
		if (node->Value == '1') return true;
		if (node->Value == '0') return false;
		return Variables[node->Value];
	}

	bool l = Solve(node->Left);
	bool r = Solve(node->Right);

	switch (node->Value)
	{
		case '|': return l | r;
		case '&': return l & r;
		case '+': return l ^ r;
		case '>': return ~l | r;
		case '=': return l == r;
		default: throw;
	}
}

std::string LogicTree::GetVariablesList(LogicTree::Node* node)
{
	std::string result = "";
	if (node->Left == nullptr || node->Right == nullptr)
	{
		result += node->Value;
		return result;
	}
	result += GetVariablesList(node->Left);
	result += GetVariablesList(node->Right);
	return result;
}

void LogicTree::SetEquation(std::string equation)
{
	equation = InfixToPostfix(equation);
	Root = SetProblem(equation);
}

