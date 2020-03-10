#include "../Include/Menu.hpp"
#include "../Include/Interaction.hpp"
#include "../Include/PriorityQueue.hpp"
//
//void InteractiveMode()
//{
//	Menu menu(InteractiveMenu, "Interaction mode");
//	auto action = InteractiveAction::Undefined;
//	list.CreateEmpty();
//	while (action != InteractiveAction::Quit)
//	{
//		action = (InteractiveAction)menu.GetAction();
//		ExecuteAction(action);
//	}
//	system("pause");
//}
//
//void DemoMode()
//{
//	std::cout << "==========Demo mode==========" << std::endl;
//	list.CreateEmpty();
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
//	DemoInsert(1, 2, 3, 0);
//	DemoInsert(2, 3, 4, 1);
//	DemoInsert(3, 4, 5, 2);
//	DemoInsert(4, 5, 6, 1);
//	DemoInsert(5, 6, 7, 0);
//	
//	DemoSet(0, 0, 0, 4);
//	DemoSet(7, 6, 5, 8);
//	list.ResetError();
//
//	DemoGet(2);
//	DemoGet(4);
//	DemoGet(6);
//	list.ResetError();
//
//	DemoRemove(3);
//	DemoRemove(3);
//	DemoRemove(0);
//	DemoRemove(6);
//	list.ResetError();
//	DemoRemove(0);
//
//	DemoInsert(1, 2, 3, 0); 
//	DemoInsert(1, 2, 3, 0);
//	DemoInsert(1, 2, 3, 0);
//
//	std::cout << "Clear()" << std::endl;
//	list.CreateEmpty();
//	PrintList();
//	std::cout << std::endl;
//
//	system("pause");
//}
//
//void BenchmarkMode()
//{
//	std::cout << "==========Benchmark mode==========" << std::endl;
//	int counter = 0;
//	list.CreateEmpty();
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//
//	double time = 0;
//	while (time < 10)
//	{
//		counter += 10000;
//		std::cout << "[" << counter << " elements]\n\n";
//		time = BenchmarkInsertBack(counter);
//		BenchmarkClearList();
//	}
//	BenchmarkInsertBack(counter);
//	BenchmarkInsertEverywhere();
//	BenchmarkRemoveEverywhere();
//
//	system("pause");
//}

int main()
{
	PriorityQuiue<int> queue;
	queue.Push(0, 0);
	queue.Push(47, 2);
	queue.Push(53, 3);
	queue.Push(69, 0);
	queue.Push(420, 0);

	std::cout << queue.Get(3) << std::endl;
	queue.Set(6, 3);
	std::cout << queue.Get(3) << std::endl;

	while (!queue.IsEmpty())
	{
		std::cout << queue.Pop() << std::endl;
	}

	Menu menu(MainMenu, "LAB_02(b)");
	auto action = MainAction::Undefined;
	while (action != MainAction::Quit)
	{
		action = (MainAction)menu.GetAction();
		switch (action)
		{
		case MainAction::Undefined:							break;
		case MainAction::Interactive:	//InteractiveMode();	break;
		case MainAction::Demo:			//DemoMode();			break;
		case MainAction::Benchmark:		//BenchmarkMode();	break;
		case MainAction::Quit:								break;
		default:											break;
		}
	}
}