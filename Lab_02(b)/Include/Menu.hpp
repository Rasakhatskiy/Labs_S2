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
    
	std::vector<std::string> MenuStringList;

    char Selector = '>';
    char Selector2 = '<';
    int Cursor;
	std::string Header;

    Button GetButton();
    void Draw();

public:
    
    Menu(std::vector<std::string> menuList, std::string header);
    void Run();
	void ResetCursor();
	int GetAction();
};


#endif //LAB_1_MENU_HPP
