#include <iostream>
#include "../Include/Graph.hpp"

int main()
{
	GraphMatrix graphMatrix(5);
	graphMatrix.GenerateRandom();
	std::cout << graphMatrix.ToStringCalc() << "\n\n";
	std::cout << graphMatrix.DFS(false) << "\n\n";
	std::cout << graphMatrix.DFS(true) << "\n\n";
	std::cout << graphMatrix.Dijkstra() << "\n\n";

	GraphStructure graphStructure(5);
	graphStructure.GenerateRandom();
	std::cout << graphStructure.ToStringCalc() << "\n\n";
	std::cout << graphStructure.DFS() << "\n\n";
}