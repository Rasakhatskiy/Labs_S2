#include "..\Include\Menu.hpp"

void Menu::Run()
{
    
}

void Menu::ResetCursor()
{
	Cursor = 0;
}

Menu::Action Menu::GetAction()
{
    Draw();
    auto button = GetButton();
	
    switch (button)
    {
        case Menu::Button::Undefined:										return Action::Move;
        case Menu::Button::Up:			
			if (Cursor > 0)Cursor--;										return Action::Move;
        case Menu::Button::Down:		
			if (Cursor < MainMenu.size() - 1)	Cursor++;					return Action::Move;
		case Menu::Button::Select:											return (Action)Cursor;
        case Menu::Button::Return:											return Action::Undefined;
        case Menu::Button::Quit:											return Action::Quit;
        default:															break;
    }
																			return Action::Undefined;
}

Menu::Menu()
{
    Cursor = 0;
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

	std::vector<std::string> menu = MainMenu;
	std::cout << "==========" + APPNAME + "==========";
	for (unsigned i = 0; i < menu.size(); ++i)
	{
		if (Cursor == i)	std::cout << Selector;
		else				std::cout << " ";

		std::cout << menu[i];

		if (Cursor == i)	std::cout << Selector2;

		std::cout << std::endl;
	}
}