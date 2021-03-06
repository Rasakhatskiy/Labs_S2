#include <conio.h>
#include <iostream>
#include "..\Include\Operator.hpp"
#include "..\Include\Menu.hpp"
#include "..\Include\DateTime.hpp"

int main() 
{
    auto _menu = Menu();
	auto _operator = Operator();
    auto action = Menu::Action();

	_operator.Benchmark();

    _operator.LoadIDs();
    while ((action = _menu.GetAction()) != Menu::Action::Quit)
    {
        switch (action)
        {
            case Menu::Action::Add:				_operator.Add();			break;

            case Menu::Action::SaveText:		_operator.SaveText();		break;
            case Menu::Action::SaveBin:			_operator.SaveBin();		break;
			case Menu::Action::ChangeTextPath:	/*todo*/					break;
			case Menu::Action::ChangeBinPath:	/*todo*/					break;

            case Menu::Action::LoadBin:			_operator.LoadBin();		break;
			case Menu::Action::LoadText:		_operator.LoadText();		break;
                
            case Menu::Action::Print:			_operator.PrintMemory();	break;

			case Menu::Action::SearchText:		_operator.SearchText();		break;
			case Menu::Action::SearchRateAuthor:_operator.SerchRateAuthor();break;
			case Menu::Action::SearchTypeTime:	_operator.SearchTypeTime();	break;

			case Menu::Action::ModifyText:		_operator.ModifyText();		break;
			case Menu::Action::ModifyBin:		_operator.ModifyBin();		break;

            case Menu::Action::Edit:			/*todo*/					break;
            case Menu::Action::Remove:			/*todo*/					break;
            case Menu::Action::Quit:										return 0;
            case Menu::Action::Undefined:		_menu.ResetCursor();		break;
            case Menu::Action::Move:										break;
            default:														break;
        }
    }
    return 0;
}
