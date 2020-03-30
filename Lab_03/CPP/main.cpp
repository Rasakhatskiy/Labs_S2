#include "../Include/Point.hpp"
#include "../Include/Sort.hpp"
#include "../Include/Menu.hpp"
#include "../Include/Interaction.hpp"

#include <iostream>

std::vector<std::string> MainMenuStrings =
{
	"Interactive mode",
	"Benchmark mode",
	"Quit"
};

std::vector<std::string> InteractiveMenuStrings =
{
	"Shuffle (and remember)",
	"Insertion sort",
	"Quick sort",
	"Merge sort",
	"Back"
};

enum MenuType 
{
	Main, Interactive
};





int main()
{
	Menu mainMenu(MainMenuStrings, "Lab 03 A");
	Menu interactiveMenu(InteractiveMenuStrings, "Interactive mode");
	Menu menu = mainMenu;
	MenuType menuType = MenuType::Main;

	bool ulala = true;

	while (ulala)
	{
		int act = menu.GetAction();
		if (act == -1) continue;
		if (menuType == MenuType::Main)
		{
			switch (act)
			{
				case 0:
					menuType = MenuType::Interactive; 
					menu = interactiveMenu;
					break;
				case 1: LaunchBenchmark(); break;
				case 2: default: ulala = false; break;
			}
			continue;
		}
		if (menuType == MenuType::Interactive)
		{
			switch (act)
			{
				case 0: Shuffle(); break;
				case 1: InsertionSortLaunch(); break;
				case 2: QuickSortLaunch(); break;
				case 3: MergeSortLaunch(); break;
				case 4: default: 
					menuType = MenuType::Main; 
					menu = mainMenu; 
					break;
			}
			continue;
		}
	}



}