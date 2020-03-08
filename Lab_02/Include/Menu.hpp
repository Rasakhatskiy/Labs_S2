#ifndef LAB_1_MENU_HPP
#define LAB_1_MENU_HPP

#include <string>
#include <iostream>
#include <conio.h>
#include <vector>

class Menu
{
private:
    enum class Button
    {
        Undefined, Up, Down, Select, Return, Quit
    };
    
    std::vector<std::string> MainMenu =
    {
        "Insert",
        "Get",
        "Set",
        "Remove",
		"Print",
		"Clear",
		"Exit"
    };

    char Selector = '>';
    char Selector2 = '<';
    int Cursor;


    Button GetButton();
    void Draw();

public:
    enum class Action
    {
        Insert,		
		Get,		
		Set,		
		Remove,		
		Print,	
		Clear,
		Quit,		
		Undefined,	
		Move		
    };
    Menu();
    void Run();
	void ResetCursor();
    Action GetAction();
};


#endif //LAB_1_MENU_HPP
