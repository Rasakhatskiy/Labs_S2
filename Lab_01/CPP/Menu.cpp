#include "..\Include\Menu.hpp"

void Menu::Run()
{
    
}

Menu::Action Menu::GetAction()
{
    Draw();
    auto button = GetButton();
    switch (button)
    {
        case Menu::Button::Undefined:
            return Action::Undefined;
            break;
        case Menu::Button::Up:
            if (Cursor > 0) Cursor--;
            break;
        case Menu::Button::Down:
            if (Cursor < MainMenuLength - 1) Cursor++;
            break;
        case Menu::Button::Select:
            //Main menu
            if (CurrentMenu == MenuType::Main && Cursor == 1)
            {
                Cursor = 0;
                CurrentMenu = MenuType::Save;
                return Action::Undefined;
            }
            if (CurrentMenu == MenuType::Main && Cursor == MainMenuLength - 1)
            {
                return Action::Quit;
                break;
            }

            //Save manu
            if (CurrentMenu == MenuType::Save && Cursor == SaveMenuLength - 1)
            {
                Cursor = 0;
                CurrentMenu = MenuType::Main;
                return Action::Undefined;
                break;
            }
            
            //General
            if(CurrentMenu == MenuType::Main) return (Action)(Cursor + 0);
            if(CurrentMenu == MenuType::Save) return (Action)(Cursor + 7);
            break;
        case Menu::Button::Return:
            return Action::Undefined;
            break;
        case Menu::Button::Quit:
            return Action::Quit;
            break;
        default:
            break;
    }
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
        case 119: case 72: return Button::Up;
        //case 97: case 75: 
        case 115: case 80: return Button::Down;
        //case 100: case 77:
        case 113: case 81: return Button::Quit;
        case 13: return Button::Select;
        case 8: return Button::Return;
        default: return Button::Undefined;
    }
}

void Menu::Draw()
{
    system("CLS");

    switch (CurrentMenu)
    {
        case Menu::MenuType::Main:
            for (int i = 0; i < MainMenuLength; ++i)
            {
                if (Cursor == i) std::cout << Selector;
                else std::cout << " ";
                std::cout << MainMenu[i] << std::endl;
            }
            break;
        case Menu::MenuType::Save:
            for (int i = 0; i < SaveMenuLength; ++i)
            {
                if (Cursor == i) std::cout << Selector;
                else std::cout << " ";
                std::cout << SaveMenu[i] << std::endl;
            }
            break;
        default:
            break;
    }

    
}


