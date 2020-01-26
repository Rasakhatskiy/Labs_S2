#ifndef LAB_1_MENU_HPP
#define LAB_1_MENU_HPP

#include <string>
#include <iostream>
#include <conio.h>

class Menu
{
    enum class MenuType 
    {
        Main, Save
    };
    MenuType CurrentMenu = MenuType::Main;
private:
    enum class Button
    {
        Undefined, Up, Down, Select, Return, Quit
    };
    
    const int MainMenuLength = 8;
    std::string MainMenu[8] =
    {
        "Add new message",
        "Save to file",
        "Load from file",
        "Print",
        "Search",
        "Edit",
        "Remove",
        "Exit",
    };

    const int SaveMenuLength = 5;
    std::string SaveMenu[5] =
    {
        "Save to text",
        "Save to bin",
        "Change text file path",
        "Change bin file path",
        "Back",
    };

    char Selector = '>';
    int Cursor;


    Button GetButton();
    void Draw();

public:
    enum class Action
    {
        Add, Save, Load, Print, Search, Edit, Remove, //Main menu
        SaveText, SaveBin, ChangeTextPath, ChangeBinPath, //Save menu
        Undefined, Quit, // General
    };
    Menu();
    void Run();
    Action GetAction();
};


#endif //LAB_1_MENU_HPP
