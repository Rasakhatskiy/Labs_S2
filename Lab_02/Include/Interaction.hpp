#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "..\Include\List.hpp"
#include "..\Include\Point.hpp"
#include "..\Include\Menu.hpp"
#include <string>
#include <thread>


List<Point3D> list;
const int WAIT_MS = 1000;

std::vector<std::string> MainMenu = {
	"Interaction mode",
	"Demo mode",
	"Benchmark mode",
	"Quit"
};

enum class MainAction
{
	Undefined = -1,
	Interactive,
	Demo,
	Benchmark,
	Quit
};

std::vector<std::string> InteractiveMenu = {

	"Insert",
	"Get",
	"Set",
	"Remove",
	"Print",
	"Clear",
	"Quit"
};

enum class InteractiveAction
{
	Undefined = -1,
	Insert,
	Get,
	Set,
	Remove,
	Print,
	Clear,
	Quit,
};



Point3D ReadPoint()
{
	Point3D point;

	std::cout << "Enter X: ";
	std::cin >> point.X;
	while (std::cin.fail())
	{
		std::cin.clear(); // put us back in 'normal' operation mode
		std::cin.ignore(32767, '\n'); // and remove the bad input
		std::cout << "Enter X: ";
		std::cin >> point.X;
	}

	std::cout << "Enter Y: ";
	std::cin >> point.Y;
	while (std::cin.fail())
	{
		std::cin.clear(); // put us back in 'normal' operation mode
		std::cin.ignore(32767, '\n'); // and remove the bad input
		std::cout << "Enter Y: ";
		std::cin >> point.Y;
	}

	std::cout << "Enter Z: ";
	std::cin >> point.Z;
	while (std::cin.fail())
	{
		std::cin.clear(); // put us back in 'normal' operation mode
		std::cin.ignore(32767, '\n'); // and remove the bad input
		std::cout << "Enter Z: ";
		std::cin >> point.Z;
	}

	return point;
}

void PrintPoint(Point3D point)
{
	std::cout << "("
		<< point.X << "; "
		<< point.Y << "; "
		<< point.Z << ")"
		<< std::endl;
}

int ReadIndex()
{
	int index;
	std::cout << "Enter Index: ";
	std::cin >> index;
	while (std::cin.fail())
	{
		std::cin.clear(); // put us back in 'normal' operation mode
		std::cin.ignore(32767, '\n'); // and remove the bad input
		std::cout << "Enter Index: ";
		std::cin >> index;
	}
	return index;
}

void PrintList(bool pause = true)
{
	if(!list.IsEmpty())
	{ 
		auto root = list.GetRoot();
		PrintPoint(root->Value);
		auto node = root->Next;
		while (node != root)
		{
			PrintPoint(node->Value);
			node = node->Next;
		}
	}
	else
	{
		std::cout << "[Empty]" << std::endl;
	}
	
	std::cout << "[" << (list.IsError() ? "Error" : "OK") << "]" << std::endl;
	if(pause) system("pause");
}

void ExecuteAction(InteractiveAction action)
{
	if (action == InteractiveAction::Quit || action == InteractiveAction::Undefined)
		return;

	if (action == InteractiveAction::Clear)
	{
		list.CreateEmpty();
	}

	if (action == InteractiveAction::Insert)
	{
		list.Insert(ReadPoint(), ReadIndex());
	}

	if (action == InteractiveAction::Print)
	{
		PrintList();
	}

	if (action == InteractiveAction::Get)
	{
		PrintPoint(list.Get(ReadIndex()));
		system("pause");
	}

	if (action == InteractiveAction::Set)
	{
		list.Set(ReadPoint(), ReadIndex());
	}

	if (action == InteractiveAction::Remove)
	{
		list.Remove(ReadIndex());
	}
}

void DemoInsert(double x, double y, double z, double i)
{
	std::cout << "Insert((" << x << "; " << y << "; " << z << "), " << i << ")" << std::endl;
	list.Insert(Point3D(x, y, z), i);
	PrintList(false);
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
}

void DemoRemove(double i)
{
	std::cout << "Remove(" << i << ")" << std::endl;
	list.Remove(i);
	PrintList(false);
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
}

void DemoSet(double x, double y, double z, double i)
{
	std::cout << "Set((" << x << "; " << y << "; " << z << "), " << i << ")" << std::endl;
	list.Set(Point3D(x, y, z), i);
	PrintList(false);
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
}

void DemoGet(double i)
{
	std::cout << "Get(" << i << ")" << std::endl;
	auto point = list.Get(i);

	if (list.IsError())
		std::cout << "[Error]" << std::endl;
	else
		PrintPoint(point);

	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_MS));
}

#endif // !INTERACTION_HPP

