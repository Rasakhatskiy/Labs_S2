#include <iostream>
#include "../Include/TreeInt.hpp"
#include "../Include/LogicTree.hpp"
#include "../Include/Menu.hpp"

std::vector<std::string> MainMenuStrings =
{
	"Tree",
	"Binary Tree",
	"Logic Tree",
	"Alt + F4"
};

std::vector<std::string> TreeStrings =
{
	"Insert Value",
	"Remove Value",
	"Print Tree",
	"Back"
};

std::vector<std::string> BinaryTreeStrings =
{
	"Insert Value",
	"Get Data",
	"Print Tree",
	"Back"
};

std::vector<std::string> LogicTreeStrings =
{
	"Set Equation",
	"Solve Equation",
	"Print Tree",
	"Back"
};

enum MenuType
{
	Main, Int, Binary, Logic
};

int ReadPositiveInteger()
{
	std::cout << "Enter integer" << std::endl;
	int x;
	std::cin >> x;
	while (std::cin.fail() || x < 0) {
		std::cout << "Invalid input! Enter positive integer! Not a character, INTEGER!!! It may look like this: 47" << std::endl;
		std::cout << "If it looks like Ɉɛɱɢɫɥɢɬɢ or -1, please, call exorcist." << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	return x;
}

int ReadInteger()
{
	std::cout << "Enter integer" << std::endl;
	int x;
	std::cin >> x;
	while (std::cin.fail()) {
		std::cout << "Invalid input! Enter integer! Not a character, INTEGER!!! It may look like this: 47" << std::endl;
		std::cout << "If it looks like Ɉɛɱɢɫɥɢɬɢ or -1, please, call exorcist." << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	return x;
}

float ReadChance()
{
	std::cout << "Enter chance from 1 too 100 (integer)" << std::endl;
	int x;
	std::cin >> x;
	while (std::cin.fail() || x < 0 || x > 100) {
		std::cout << "Invalid input! Enter positive integer! Not a character, INTEGER!!! It may look like this: 47" << std::endl;
		std::cout << "If it looks like Ɉɛɱɢɫɥɢɬɢ or -1, please, call exorcist." << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> x;
	}
	return x / 100.0;
}

std::string VecDataToStr(std::vector<long> vector)
{
	std::string result = "";
	for (auto& i : vector)
		result += std::to_string(i) + " ";
	return result;
}

void ReadEquation(LogicTree& tree)
{
	std::cin.ignore();
	tree.DeleteNode(tree.Root);
	std::cout << "\n& - and\n| - or \n+ - xor\n> - implication\n= - equality\n" << std::endl;
	std::cout << "Write equation : " << std::endl;
	std::string equation;
	std::getline(std::cin, equation);
	tree.SetEquation(equation);
	std::string vars = tree.GetVariablesList(tree.Root);
	vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
	std::map<char, bool> map;
	for (auto& i : vars)
	{
		std::cout << "Enter value of \'" << i << "\' : ";
		bool b; std::cin >> b;
		map[i] = b;
	}
	tree.Variables = map;
}

int main()
{
	Menu mainMenu = Menu(MainMenuStrings, "Lab 04");
	Menu intMenu = Menu(TreeStrings, "Super Tree");
	Menu binTreeMenu = Menu(BinaryTreeStrings, "Binary Tree");
	Menu logTreeMenu = Menu(LogicTreeStrings, "Logic Tree");
	Menu menu(mainMenu);
	MenuType type = MenuType::Main;

	Tree intTree;
	BinaryTree binTree;
	LogicTree logTree;

	int action = 0;
	while (true)
	{
		int action = menu.GetAction();

		if (type == MenuType::Main)
		{
			if (action == 0) { menu = intMenu;		type = MenuType::Int; }
			if (action == 1) { menu = binTreeMenu;	type = MenuType::Binary; }
			if (action == 2) { menu = logTreeMenu;	type = MenuType::Logic; }
			if (action == 3) { return 0; }
			continue;
		}
		if (type == MenuType::Int)
		{
			if (action == 0) intTree.AddNode(intTree.Root, ReadInteger(), ReadChance());
			if (action == 1) intTree.DeleteNode(ReadInteger());
			if (action == 2) std::cout << intTree.ToString() << std::endl;
			if (action == 3) { menu = mainMenu;		type = MenuType::Main; }
			if (action == 2)
			{
				std::cout << "Press F to pay respects..." << std::endl;
				_getch();
			}
			continue;
		}
		if (type == MenuType::Binary)
		{
			if (action == 0) binTree.AddNode(ReadInteger());
			if (action == 1) std::cout << VecDataToStr(binTree.GetData()) << std::endl;
			if (action == 2) std::cout << binTree.ToString() << std::endl;
			if (action == 3) { menu = mainMenu;		type = MenuType::Main; }
			if (action == 2 || action == 1)
			{
				std::cout << "Tadah..." << std::endl;
				_getch();
			}
			continue;
		}
		if (type == MenuType::Logic)
		{
			if (action == 0) ReadEquation(logTree);
			if (action == 1) std::cout << "Result : " << logTree.Solve() << std::endl;
			if (action == 2) std::cout << logTree.ToString() << std::endl;
			if (action == 3) { menu = mainMenu;		type = MenuType::Main; }
			if (action == 2 || action == 1)
			{
				std::cout << "...---..." << std::endl;
				_getch();
			}
			continue;
		}
	}
}