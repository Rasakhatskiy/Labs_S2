#ifndef LAB_1_MENU_HPP
#define LAB_1_MENU_HPP

#include <string>
#include <iostream>
#include <conio.h>

class Menu
{
private:
    enum class Button
    {
        Undefined, Up, Down, Select, Return, Quit
    };
    
    std::string MenuList[7] =
        {
        "Add new message",
        "Save to file",
        "Load from file",
        "Print",
        "Search",
        "Edit",
        "Remove",
        };

    char Selector = '>';
    int Length = 7;
    int Cursor;


    Button GetButton();
    void Draw();

public:
    enum class Action
    {
        Add, Save, Load, Print, Search, Edit, Remove, Quit, Undefined
    };
    Menu();
    void Run();
    Action GetAction();
};


#endif //LAB_1_MENU_HPP
