#include "../Include/Point.hpp"
#include "../Include/Sort.hpp"
#include "../Include/Menu.hpp"
#include "../Include/Interaction.hpp"

#include <iostream>
#include <algorithm>

std::string SortingOrder;

std::vector<std::string> MainMenuStrings =
{
	"Points",
	"Messages",
	"Quit"
};

std::vector<std::string> PointsMenuStrings =
{
	"Shuffle (and remember)",
	"Set sorting order",
	"Sort",
	"Print",
	"Back"
};

std::vector<std::string> SortingOrderMenuStrings =
{
	"X",
	"Y",
	"Z"
};

enum MenuType 
{
	Main, Points, Messages, Selector
};

struct bigger_than_key
{
	inline bool operator() (const Point3D& struct1, const Point3D& struct2)
	{
		for (int i = 0; i < 3; i++)
		{
			switch (SortingOrder[0])
			{
				case'X': 
					if (struct1.X > struct2.X) return true;
					else if (struct1.X == struct2.X) break;
					else return false;
				case'Y': 
					if (struct1.Y > struct2.Y) return true;
					else if (struct1.Y == struct2.Y) break;
					else return false;
				case'Z':
					if (struct1.Z > struct2.Z) return true;
					else if (struct1.Z == struct2.Z) break;
					else return false;
				default: throw;
			}
		}
		return false;
	}
};



int main()
{
	SortingOrder = "XYZ";
	Menu mainMenu(MainMenuStrings, "Lab 03 A");
	Menu pointsMenu(PointsMenuStrings, "Interactive mode");
	Menu menu = mainMenu;
	MenuType menuType = MenuType::Main;

	std::vector<std::string> tempVec(SortingOrderMenuStrings);
	Menu orderMenu(tempVec, "    _    _    _    ");


	int setup = 0;
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
					menuType = MenuType::Points;
					menu = pointsMenu;
					break;
				case 1: LaunchBenchmark(); break;
				case 2: default: ulala = false; break;
			}
			continue;
		}
		if (menuType == MenuType::Points)
		{
			switch (act)
			{
				case 0: Shuffle(); break;
				case 1: 
					SortingOrder.clear();
					menuType = MenuType::Selector;
					tempVec = std::vector<std::string>(SortingOrderMenuStrings);
					menu = Menu(tempVec, "    _    _    _    ");
					setup = 0;
					break;
				case 2:
					std::sort(&MOTHER_ARRAY[0], &MOTHER_ARRAY[SIZE], bigger_than_key());
					std::cout << "Sort has been committed" << std::endl;
					_getch();
					break;
				case 3: 
					PrintArray(MOTHER_ARRAY, SIZE); 
					std::cout << "Press Alt + F4 to close the programm or any other key to continue..." << std::endl;
					_getch();
					break;
				case 4: default: 
					menuType = MenuType::Main; 
					menu = mainMenu; 
					break;
			}
			continue;
		}
		if (menuType == MenuType::Messages)
		{

			continue;
		}
		if (menuType == MenuType::Selector) 
		{
			SortingOrder += tempVec[act];
			menu.Header[setup++ * 5 + 4] = tempVec[act][0];
			tempVec.erase(tempVec.begin() + act);
			menu = Menu(tempVec, menu.Header);
			menu.ResetCursor();

			if (tempVec.size() == 0)
			{
				menuType = MenuType::Points;
				menu = pointsMenu;
				setup = 0;
			}
			continue;
		}
	}



}