#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "..\Include\List.hpp"
#include "..\Include\Point.hpp"
#include "..\Include\Menu.hpp"
#include <string>
#include <thread>
#include <random>


List<Point3D> list;
std::vector<Point3D> vector;
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


Point3D GetRandomPoint()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 random_shit(rd());//some shit i don't know
	std::uniform_int_distribution<> distribution(-INT_MAX, INT_MAX); // define the range
	return Point3D((distribution(random_shit)), (distribution(random_shit)), (distribution(random_shit)));
}

double BenchmarkInsertBack(int number)
{
	auto begin = std::chrono::steady_clock::now();
	for (int i = 0; i < number; i++)
		list.Insert(Point3D(i, i, i), list.Length());
	auto end = std::chrono::steady_clock::now();

	double timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
	int memoryList = list.GetSize();


	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < number; i++)
		vector.push_back(Point3D(i, i, i));
	end = std::chrono::steady_clock::now();

	double timeVector = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
	int memoryVector = sizeof(Point3D) * vector.size() + sizeof(std::vector<Point3D>);


	std::cout << "+++++Insertion to back++++ " << std::endl;
	std::cout
		<< "List elapsed time: "
		<< timeList
		<< " seconds" << std::endl;

	std::cout
		<< "List memory taken: "
		<< (memoryList > 1024 ? memoryList / 1024.0 : memoryList)
		<< (memoryList > 1024 ? " KB" : " B") << std::endl;
	std::cout << "[" << (list.IsError() ? "Error" : "OK") << "]" << std::endl;

	std::cout
		<< "Vector elapsed time: "
		<< timeVector
		<< " seconds" << std::endl;

	std::cout
		<< "Vector memory taken: "
		<< (memoryVector > 1024 ? memoryVector / 1024.0 : memoryVector)
		<< (memoryVector > 1024 ? " KB" : " B") << std::endl;


	std::cout << std::endl;
	return timeList;
}

double BenchmarkClearList()
{
	auto begin = std::chrono::steady_clock::now();
	int length = list.Length();
	list.CreateEmpty();
	auto end = std::chrono::steady_clock::now();

	double timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
	int memoryList = list.GetSize();


	begin = std::chrono::steady_clock::now();
	vector.clear();
	end = std::chrono::steady_clock::now();

	double timeVector = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
	int memoryVector = vector.size() * sizeof(Point3D) + sizeof(std::vector<Point3D>);

	std::cout << "-----Clearing-----" << std::endl;

	std::cout
		<< "List elapsed time: "
		<< timeList
		<< " seconds" << std::endl;

	std::cout
		<< "List memory taken: "
		<<  (memoryList > 1024 ? memoryList / 1024.0 : memoryList)
		<< (memoryList > 1024 ? " KB" : " B") << std::endl;

	std::cout << "[" << (list.IsError() ? "Error" : "OK") << "]" << std::endl;

	std::cout
		<< "Vector elapsed time: "
		<< timeVector
		<< " seconds" << std::endl;

	std::cout
		<< "Vector memory taken: "
		<< (memoryVector > 1024 ? memoryVector / 1024.0 : memoryVector)
		<< (memoryVector > 1024 ? " KB" : " B") << std::endl;

	std::cout << std::endl;
	std::cout << ".............................................." << std::endl;
	std::cout << std::endl;
	return timeList;
}

void BenchmarkGet()
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;
	auto point = Point3D();
	for (int i = 0; i < list.Length(); i += 1000)
	{
		begin = std::chrono::steady_clock::now();
		point = list.Get(i);
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0;
		std::cout << "Element #" << i << std::endl;
		std::cout
			<< "Access time: "
			<< time
			<< " seconds" << std::endl;
		std::cout << std::endl;
	}
}

void BenchmarkInsertEverywhere()
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;
	auto point = Point3D(0, 0, 0);

	std::cout << "+++++List insertion+++++" << std::endl;
	for (int i = 0; i < list.Length(); i += 1000)
	{
		begin = std::chrono::steady_clock::now();
		list.Insert(point, i);
		end = std::chrono::steady_clock::now();

		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Element #" << i << std::endl;
		std::cout
			<< "Insertion time: "
			<< time
			<< " miliseconds" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "+++++Vector insertion+++++" << std::endl;
	for (int i = 0; i < vector.size(); i += 1000)
	{
		begin = std::chrono::steady_clock::now();
		vector.insert(vector.begin() + i, point);
		end = std::chrono::steady_clock::now();

		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Element #" << i << std::endl;
		std::cout
			<< "Insertion time: "
			<< time
			<< " miliseconds" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void BenchmarkRemoveEverywhere()
{
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto time = 0.0;
	auto point = Point3D(0, 0, 0);

	std::cout << "+++++List remove+++++" << std::endl;
	for (int i = 0; i < list.Length(); i += 1000)
	{
		begin = std::chrono::steady_clock::now();
		list.Remove(i);
		end = std::chrono::steady_clock::now();

		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Element #" << i << std::endl;
		std::cout
			<< "Removing time: "
			<< time
			<< " miliseconds" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "+++++Vector remove+++++" << std::endl;
	for (int i = 0; i < vector.size(); i += 1000)
	{
		begin = std::chrono::steady_clock::now();
		vector.erase(vector.begin() + i);
		end = std::chrono::steady_clock::now();

		time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
		std::cout << "Element #" << i << std::endl;
		std::cout
			<< "Removing time: "
			<< time
			<< " miliseconds" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
#endif // !INTERACTION_HPP

