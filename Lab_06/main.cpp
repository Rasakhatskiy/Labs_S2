
#include "Interaction.hpp"
#include "FlawlessMenu.hpp"

#include <iostream>
#include <conio.h>

int main()
{
	FlawlessMenu::Menu::Filler = "=============";
	FlawlessMenu::Menu::Selector = "==>";
	FlawlessMenu::Menu::GetKeyFunc = _getch;


	auto Create = new FlawlessMenu::Menu("Choose your list");
	Create->Add("Linked list", SLL_Create);
	Create->Add("Array list", SAL_Create);
	Create->Add("Binary search tree", BST_Create);
	Create->Add("AVL tree", AVL_Create);
	Create->Add("2-3 tree", TTT_Create);

	auto Interactive = new FlawlessMenu::Menu("Interactive mode");
	Interactive->Add("Create list", Create);
	Interactive->Add("Insert value", Insert);
	Interactive->Add("Remove value", Remove);
	Interactive->Add("Search for value", Search);
	Interactive->Add("Show list", Show);

	auto Menu = new FlawlessMenu::Menu("Main menu");
	Menu->Add("Interactive mode", Interactive);
	Menu->Add("Demo mode", Demo);
	Menu->Add("Benchmark mode", Benchmark);

	Menu->Start();
}