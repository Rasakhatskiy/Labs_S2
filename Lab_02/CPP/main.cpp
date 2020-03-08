#include "../Include/Interaction.hpp"

void InteractiveMode()
{
	Menu menu;
	Menu::Action action = Menu::Action::Undefined;
	list.CreateEmpty();
	while (action != Menu::Action::Quit)
	{
		action = menu.GetAction();
		ExecuteAction(action);
	}
	system("pause");
}


int main()
{
	
}