#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "..\Include\List.hpp"
#include "..\Include\Point.hpp"
#include "..\Include\Menu.hpp"
#include <string>

List<Point3D> list;

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

void PrintList()
{
	auto root = list.GetRoot();
	PrintPoint(root->Value);
	auto node = root->Next;
	while (node != root)
	{
		PrintPoint(node->Value);
		node = node->Next;
	}
	system("pause");
}

void ExecuteAction(Menu::Action action)
{
	if (action == Menu::Action::Quit || action == Menu::Action::Undefined)
		return;

	if (action == Menu::Action::Clear)
	{
		list.CreateEmpty();
	}

	if (action == Menu::Action::Insert)
	{
		list.Insert(ReadPoint(), ReadIndex());
	}

	if (action == Menu::Action::Print)
	{
		PrintList();
	}

	if (action == Menu::Action::Get)
	{
		PrintPoint(list.Get(ReadIndex()));
		system("pause");
	}

	if (action == Menu::Action::Set)
	{
		list.Set(ReadPoint(), ReadIndex());
	}

	if (action == Menu::Action::Remove)
	{
		list.Remove(ReadIndex());
	}
}

#endif // !INTERACTION_HPP

