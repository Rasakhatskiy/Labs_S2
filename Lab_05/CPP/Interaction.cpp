#include "../Include/Interaction.hpp"

Graph* graph = nullptr;

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

}

void Benchmark() 
{
}

void ShowGraph()
{
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
	if (graph->CheckConnectivity())
		std::cout << "Graph is continuous.\n";
	else
		std::cout << "Graph is not continuous.\n";
	std::cout << "press any key, blah blah...";
	_getch();
}

void DFSA()
{
	std::cout << graph->DFS(false) << std::endl;
	std::cout << "wait...";
	_getch();
}

void DFSS()
{
	std::cout << graph->DFS(true) << std::endl;
	std::cout << "sample text";
	_getch();
}

void Dijkstra()
{
	std::cout << graph->Dijkstra() << std::endl;
	std::cout << "[game is paused]";
	_getch();
}

void KahnsSort()
{
	std::cout << graph->KahnsSort() << std::endl;
	std::cout << "Hello, world!";
	_getch();
}

void FindMST()
{
	std::cout << graph->FindMST()->ToString() << std::endl;
	std::cout << "Funy joke, haha, how original, such funny...";
	_getch(); 
}

void KruskalMST()
{
	std::cout << graph->KruskalMST()->ToString() << std::endl;
	std::cout << "I hate coronovirus. Press any key...";
	_getch();
}