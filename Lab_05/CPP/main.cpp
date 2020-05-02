#include <iostream>
#include "../Include/Graph.hpp"

int main()
{
	GraphMatrix graphMatrix(5);
	graphMatrix.GenerateRandom();
	std::cout << graphMatrix.ToStringCalc();

	std::cout << std::endl;

	GraphStructure graphStructure(5);
	graphStructure.GenerateRandom();
	std::cout << graphStructure.ToString();
}