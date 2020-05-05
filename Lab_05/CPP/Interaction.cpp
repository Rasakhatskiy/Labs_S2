#include "../Include/Interaction.hpp"

Graph* graph = nullptr;

void Sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int ReadSize()
{
	std::cout << "Enter size: ";
	int size; std::cin >> size;
	while (!std::cin.good() || size <= 0)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "I can tell that you are not a robot, because robots can't be so stupid" << std::endl;
		std::cout << "Enter size: ";
		std::cin >> size;
	}
	return size;
}

char ReadChar()
{
	char size; std::cin >> size;
	while (!std::cin.good() || size <= 0)
	{
		std::cin.clear();
		std::cin.ignore(CHAR_MAX, '\n');
		std::cin >> size;
	}
	return size;
}

int ReadVertex()
{
	std::cout << "Enter Vertex id: ";
	int size; std::cin >> size;
	while (!std::cin.good() || size < 0 || size >= graph->GetSize())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "No! You are wrong!" << std::endl;
		std::cout << "Enter Vertex id: ";
		std::cin >> size;
	}
	return size;
}

int ReadWeight()
{
	std::cout << "Enter weight: ";
	int size; std::cin >> size;
	while (!std::cin.good() || size <= 0)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "You have to watch some tutorials about how to enter integer values" << std::endl;
		std::cout << "Enter weight: ";
		std::cin >> size;
	}
	return size;
}



void Demo() 
{
	std::cout << "Let's create random 25-vertex graph.\n";
	graph = new GraphMatrix(25);
	std::cout << graph->ToString() << std::endl;
	std::cout << graph->CheckConnectivity() << std::endl;
	if (graph->CheckConnectivity())
		std::cout << "Graph is continuous.\n";
	else
		std::cout << "Graph is not continuous.\n";
	Sleep();
	std::cout << "Depth First Search by any vertex" << std::endl;
	std::cout << graph->DFS(false) << std::endl;
	Sleep();
	std::cout << "Depth First Search from hightest weight of edge" << std::endl;
	std::cout << graph->DFS(true) << std::endl;
	Sleep();
	std::cout << "Find shortest path by Dijkstra algorythm" << std::endl;
	std::cout << graph->Dijkstra() << std::endl;
	Sleep();
	std::cout << "Kahn's topologic sort" << std::endl;
	std::cout << graph->KahnsSort() << std::endl;
	Sleep();
	std::cout << "Find Minimum Spanning Tree" << std::endl;
	std::cout << graph->FindMST()->ToString() << std::endl;
	Sleep();
	std::cout << "Find Kruskal Minimum Spanning Tree" << std::endl;
	std::cout << graph->KruskalMST()->ToString() << std::endl;
	Sleep();
	std::cout << "This was a demo version application. \n" <<
		"You can get the full version by giving me maximum points per semester.\n" <<
		"Press any key to continue..."<< std::endl;
	_getch();
}

void Benchmark() 
{
}

bool CheckNullptr()
{
	if (graph == nullptr)
	{
		std::cout << "Create graph first!\n..." << std::endl;
		_getch();
		return true;
	}
	return false;
}

void ShowGraph()
{
	if (CheckNullptr())return;
	std::cout << graph->ToString();
	_getch();
}

void FillMatrixRandom()
{
	graph = new GraphMatrix(ReadSize());
	graph->GenerateRandom();
}

void FillMatrixByHand()
{
	graph = new GraphMatrix(ReadSize());
	do
	{
		std::cout << "Add edge? (y/n) : ";
		char ch = ReadChar();
		if (ch != 'y' && ch != 'Y')
			break;

		int v1 = ReadVertex();
		int v2 = ReadVertex();
		int w = ReadWeight();
		graph->AddEdge(v1, v2, w);
	} while (true);
}

void FillStructureRandom()
{
	graph = new GraphStructure(ReadSize());
	graph->GenerateRandom();
}

void FillStructureByHand()
{
	graph = new GraphStructure(ReadSize());
	do
	{
		std::cout << "Add edge? (y/n) : ";
		char ch = ReadChar();
		if (ch != 'y' && ch != 'Y')
			break;

		int v1 = ReadVertex();
		int v2 = ReadVertex();
		int w = ReadWeight();
		graph->AddEdge(v1, v2, w);
	} while (true);
}

void CheckConnectivity()
{
	if (CheckNullptr())return;
	if (graph->CheckConnectivity())
		std::cout << "Graph is continuous.\n";
	else
		std::cout << "Graph is not continuous.\n";
	std::cout << "press any key, blah blah...";
	_getch();
}

void DFSA()
{
	if (CheckNullptr())return;
	std::cout << graph->DFS(false) << std::endl;
	std::cout << "wait...";
	_getch();
}

void DFSS()
{
	if (CheckNullptr())return;
	std::cout << graph->DFS(true) << std::endl;
	std::cout << "sample text";
	_getch();
}

void Dijkstra()
{
	if (CheckNullptr())return;
	std::cout << graph->Dijkstra() << std::endl;
	std::cout << "[game is paused]";
	_getch();
}

void KahnsSort()
{
	if (CheckNullptr())return;
	std::cout << graph->KahnsSort() << std::endl;
	std::cout << "Hello, world!";
	_getch();
}

void FindMST()
{
	if (CheckNullptr())return;
	std::cout << graph->FindMST()->ToString() << std::endl;
	std::cout << "Funy joke, haha, how original, such funny...";
	_getch(); 
}

void KruskalMST()
{
	if (CheckNullptr())return;
	std::cout << graph->KruskalMST()->ToString() << std::endl;
	std::cout << "I hate coronovirus. Press any key...";
	_getch();
}




