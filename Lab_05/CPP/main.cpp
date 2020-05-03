#include <iostream>
#include "../Include/Graph.hpp"

int main()
{
	//GraphMatrix graphMatrix(5);
	//graphMatrix.GenerateRandom();

	//graphMatrix.AddEdge(0, 1, 2);
	//graphMatrix.AddEdge(1, 0, 2);
	//graphMatrix.AddEdge(0, 2, 2);
	//graphMatrix.AddEdge(2, 0, 2);
	//graphMatrix.AddEdge(0, 3, 2);
	//graphMatrix.AddEdge(3, 0, 2);
	//graphMatrix.AddEdge(0, 4, 2);
	//graphMatrix.AddEdge(4, 0, 2);
	//graphMatrix.AddEdge(1, 3, 2);

	//std::cout << graphMatrix.ToString() << "\n\n";
	//std::cout << graphMatrix.ToStringCalc() << "\n\n";
	//std::cout << graphMatrix.DFS(false) << "\n\n";
	//std::cout << graphMatrix.DFS(true) << "\n\n";
	//std::cout << graphMatrix.Dijkstra() << "\n\n";
	//std::cout << graphMatrix.KahnsSort() << "\n\n";

	//auto mst = graphMatrix.FindMST();
	//std::cout << mst->ToString() << "\n\n";
	//std::cout << mst->ToStringCalc() << "\n\n";


	//std::cout << "======================================\n\n\n";
	GraphStructure graphStructure(5);

	graphStructure.AddEdge(0, 1);
	graphStructure.AddEdge(1, 0);
	graphStructure.AddEdge(0, 2);
	graphStructure.AddEdge(2, 0);
	graphStructure.AddEdge(0, 3);
	graphStructure.AddEdge(3, 0);
	graphStructure.AddEdge(0, 4);
	graphStructure.AddEdge(4, 0);
	graphStructure.AddEdge(1, 3);

	std::cout << graphStructure.ToString() << "\n\n";
	std::cout << graphStructure.ToStringCalc() << "\n\n";

	auto mst = graphStructure.FindMST();

	std::cout << mst->ToString() << "\n\n";
	std::cout << mst->ToStringCalc() << "\n\n";

	//graphStructure.GenerateRandom();
	//std::cout << graphStructure.ToStringCalc() << "\n\n";
	//std::cout << graphStructure.DFS() << "\n\n";
	//std::cout << graphStructure.KahnsSort() << "\n\n";
}