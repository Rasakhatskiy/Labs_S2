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
            if (Cursor < Length - 1) Cursor++;
            break;
        case Menu::Button::Select:
            return (Action)Cursor;
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
    for (int i = 0; i < Length; ++i)
    {
        if (Cursor == i) std::cout << Selector;
        else std::cout << " ";
        std::cout << MenuList[i] << std::endl;
    }
}


