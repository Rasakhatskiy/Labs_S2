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

void DemoMode()
{
	std::cout << "==========Demo mode==========" << std::endl;
	list.CreateEmpty();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	DemoInsert(1, 2, 3, 0);
	DemoInsert(2, 3, 4, 1);
	DemoInsert(3, 4, 5, 2);
	DemoInsert(4, 5, 6, 1);
	DemoInsert(5, 6, 7, 0);
	
	DemoSet(0, 0, 0, 4);
	DemoSet(7, 6, 5, 8);
	list.ResetError();

	DemoGet(2);
	DemoGet(4);
	DemoGet(6);
	list.ResetError();

	DemoRemove(3);
	DemoRemove(3);
	DemoRemove(0);
	DemoRemove(6);
	list.ResetError();
	DemoRemove(0);

	DemoInsert(1, 2, 3, 0); 
	DemoInsert(1, 2, 3, 0);
	DemoInsert(1, 2, 3, 0);

	std::cout << "Clear()" << std::endl;
	list.CreateEmpty();
	PrintList();
	std::cout << std::endl;

	system("pause");
}

int main()
{
	DemoMode();
}