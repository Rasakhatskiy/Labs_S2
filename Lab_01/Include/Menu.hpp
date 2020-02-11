#ifndef LAB_1_MENU_HPP
#define LAB_1_MENU_HPP

#include <string>
#include <iostream>
#include <conio.h>
#include <vector>

class Menu
{
    enum class MenuType 
    {
        Main, Save, Load, Search
    };
    MenuType CurrentMenu = MenuType::Main;
private:
    enum class Button
    {
        Undefined, Up, Down, Select, Return, Quit
    };
    
    std::vector<std::string> MainMenu =
    {
        "Add new message",
        "Save memory to file",
        "Load from file",
        "Print",
        "Search",
        "Edit",
        "Remove",
        "Exit",
    };

	std::vector<std::string> SaveMenu =
    {
        "Save to text",
        "Save to bin",
        "Back",
    };

	std::vector<std::string> LoadMenu =
	{
		"Load from text",
		"Load from bin",
		"Back",
	};

	std::vector<std::string> SearchMenu =
	{
		"Search by text fragment",
		"Search by rate from author",
		"Search by type with time",
		"Back",
	};

    char Selector = '>';
    char Selector2 = '<';
    int Cursor;


    Button GetButton();
    void Draw();

public:
    enum class Action
    {
        Add, Save, Load, Print, Search, Edit, Remove,		//Main menu		00-06 
        SaveText, SaveBin, ChangeTextPath, ChangeBinPath,	//Save menu		07-10
		LoadText, LoadBin,									//Load menu		11-12
		SearchText, SearchRateAuthor, SearchTypeTime,		//Search menu	13-15
        Undefined, Move, Quit, // General
    };
    Menu();
    void Run();
	void ResetCursor();
    Action GetAction();
};


#endif //LAB_1_MENU_HPP
