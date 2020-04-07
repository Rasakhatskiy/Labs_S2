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
	"Clear Tree",
	"Back"
};

std::vector<std::string> BinaryTreeStrings =
{
	"Insert Value",
	"Get Data",
	"Print Tree",
	"Clear Tree",
	"Back"
};

std::vector<std::string> LogicTreeStrings =
{
	"Set Equation",
	"Solve Equation",
	"Print Tree",
	"Clear Tree",
	"Back"
};

enum MenuType
{
	Main, Tree, Binary, Logic
};

int main()
{
	Menu mainMenu = Menu(MainMenuStrings, "Lab 04");
	Menu treeMenu = Menu(MainMenuStrings, "Lab 04");
	Menu binTreeMenu = Menu(MainMenuStrings, "Lab 04");
	Menu logTreeMenu = Menu(MainMenuStrings, "Lab 04");
	Menu menu(mainMenu);
	MenuType type = MenuType::Main;

	int action = 0;
	while (true)
	{
		int action = menu.GetAction();

		if (type == MenuType::Main)
		{
			if (action == 0) { menu = treeMenu;		type = MenuType::Tree; }
			if (action == 1) { menu = binTreeMenu;	type = MenuType::Binary; }
			if (action == 2) { menu = logTreeMenu;	type = MenuType::Logic; }
			if (action == 3) { return; }
			continue;
		}
		if (type == MenuType::Tree)
		{

		}
		if (type == MenuType::Binary)
		{

		}
		if (type == MenuType::Logic)
		{

		}

	}



}