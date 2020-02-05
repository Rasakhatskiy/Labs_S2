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
    int maxMenu = 0;
    switch (CurrentMenu)
    {
        case Menu::MenuType::Main:	maxMenu = MainMenu.size();		break;
        case Menu::MenuType::Save:	maxMenu = SaveMenu.size();		break;
        case Menu::MenuType::Load:	maxMenu = LoadMenu.size();		break;
        case Menu::MenuType::Search:maxMenu = SearchMenu.size();	break;
        default: break;
    }


    switch (button)
    {
        case Menu::Button::Undefined:										return Action::Move;
        case Menu::Button::Up:			if (Cursor > 0)Cursor--;			return Action::Move;
        case Menu::Button::Down:		if (Cursor < maxMenu - 1)Cursor++;	return Action::Move; 

        case Menu::Button::Select:
		{
			//---------------------------------------------MAIN MENU------------------------------------------------------
			if (CurrentMenu == MenuType::Main)
			{
				switch (Cursor)
				{
					case 1: CurrentMenu = MenuType::Save;					return Action::Undefined;
					case 2: CurrentMenu = MenuType::Load;					return Action::Undefined;
					case 4: CurrentMenu = MenuType::Search;					return Action::Undefined;
					case 7:													return Action::Quit;
					default:												return (Action)(Cursor + 0);
				}
			}

			//---------------------------------------------SAVE MENU------------------------------------------------------
			if (CurrentMenu == MenuType::Save)
			{
				switch (Cursor)
				{
					case 2:	CurrentMenu = MenuType::Main;					return Action::Undefined;
					default:												return (Action)(Cursor + 7);
				}
			}

			//---------------------------------------------LOAD MENU------------------------------------------------------
			if (CurrentMenu == MenuType::Load)
			{
				switch (Cursor)
				{
					case 2: CurrentMenu = MenuType::Main;					return Action::Undefined;
					default:												return (Action)(Cursor + 11);
				}
			}

			//---------------------------------------------SEARCH MENU----------------------------------------------------
			if (CurrentMenu == MenuType::Search)
			{
				switch (Cursor)
				{
					case 3: CurrentMenu = MenuType::Main;					return Action::Undefined;
					default:												return (Action)(Cursor + 13);
				}
			}

			//---------------------------------------------GENERAL--------------------------------------------------------
			break;
		}
        case Menu::Button::Return:											return Action::Undefined;
        case Menu::Button::Quit:											return Action::Quit;
        default: break;
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

	std::vector<std::string> menu;

	switch (CurrentMenu)
	{
		case Menu::MenuType::Main:		menu = MainMenu;	break;
		case Menu::MenuType::Save:		menu = SaveMenu;	break;
		case Menu::MenuType::Load:		menu = LoadMenu;	break;
		case Menu::MenuType::Search:	menu = SearchMenu;	break;
	}

	for (unsigned i = 0; i < menu.size(); ++i)
	{
		if (Cursor == i)	std::cout << Selector;
		else				std::cout << " ";

		std::cout << menu[i];

		if (Cursor == i)	std::cout << Selector2;

		std::cout << std::endl;
	}
}