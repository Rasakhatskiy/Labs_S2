#include "..\Include\Menu.hpp"

Menu::Menu(std::vector<std::string> menuList, std::string header)
{
	MenuStringList = menuList;
	Cursor = 0;
	Header = header;
}

void Menu::Run()
{
    
}

void Menu::ResetCursor()
{
	Cursor = 0;
}

int Menu::GetAction()
{
    Draw();
    auto button = GetButton();
	
    switch (button)
    {
        case Menu::Button::Undefined:										return -1;
        case Menu::Button::Up:			
			if (Cursor > 0)Cursor--;										return -1;
        case Menu::Button::Down:		
			if (Cursor < MenuStringList.size() - 1)	Cursor++;				return -1;
		case Menu::Button::Select:											return Cursor;
        default:															return -1;
    }
}

Menu::Button Menu::GetButton()
{
    auto key = _getch();
    switch (key)
    {
        case 119: case 72:		return Button::Up;
        //case 97: case 75: 
        case 115: case 80:		return Button::Down;
        //case 100: case 77:
        case 113: case 81:		return Button::Quit;
        case 13:				return Button::Select;
        case 8:					return Button::Return;
        default:				return Button::Undefined;
    }
}

void Menu::Draw()
{
    system("CLS");

	std::cout << "==========" + Header + "==========";
	for (unsigned i = 0; i < MenuStringList.size(); ++i)
	{
		if (Cursor == i)	std::cout << Selector;
		else				std::cout << " ";

		std::cout << MenuStringList[i];

		if (Cursor == i)	std::cout << Selector2;

		std::cout << std::endl;
	}
}