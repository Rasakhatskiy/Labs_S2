#ifndef LOGIC_TREE_HPP
#define LOGIC_TREE_HPP

#include <vector>
#include <map>
#include <string>
#include <stack>

/*	0 - 0
	1 - 1
	& - and
	| - or
	+ - xor
	> - implication
	= - equality 
*/

class LogicTree
{
public:
	class Node
	{
	public:
		char Value;

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
	std::map<char, bool> Variables;

	void AddNode(long value);
	std::string ToString();
	std::vector<long> GetData();

	LogicTree();
	LogicTree(std::string problem);
	~LogicTree();
	std::string InfixToPostfix(std::string expression);
	bool Solve();
	bool Solve(Node* node);
	std::string GetVarList();
	void SetEquation(std::string equation);
	std::string GetVariablesList(LogicTree::Node* node);
	void DeleteNode(Node* node);
private:
	
	void AddNode(Node*& node, long value);
	std::vector<long> GetData(Node* node);
	bool IsOperator(char c);
	bool IsOperand(char c);
	Node* AddNode(int value);
	Node* SetProblem(std::string problem);
	bool HasHigherPrecedence(char op1, char op2);
	int GetOperatorWeight(char op);
};



#endif // !LOGIC_TREE_HPP