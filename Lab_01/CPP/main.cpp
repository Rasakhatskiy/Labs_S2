#include <conio.h>
#include <iostream>
#include "..\Include\Operator.hpp"
#include "..\Include\Menu.hpp"
#include "..\Include\DateTime.hpp"

int main() 
{
    auto menu = Menu();
    auto action = Menu::Action();
    auto _operator = Operator();
    while ((action = menu.GetAction()) != Menu::Action::Quit)
    {
        switch (action)
        {
            case Menu::Action::Add:
                _operator.Add();
                break;
            case Menu::Action::Save:
                break;
            case Menu::Action::Load:
                break;
            case Menu::Action::Print:
                _operator.PrintMemory();
                break;
            case Menu::Action::Search:
                break;
            case Menu::Action::Edit:
                break;
            case Menu::Action::Remove:
                break;
            case Menu::Action::Quit:
                return 0;
                break;
            case Menu::Action::Undefined:
                break;
            default:
                break;
        }
    }
    return 0;
}