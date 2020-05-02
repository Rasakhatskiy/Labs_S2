#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <random>
#include <string>

class Graph
{
protected:
	int Size;
	bool* Visited;
	std::random_device RandomDevice;
	std::mt19937 RandomGenerator;
	std::uniform_int_distribution<int> RandomDistributorInt;
	std::uniform_int_distribution<int> RandomDistributorBool;

	int GetRandomInt();
	bool GetRandomBool();

public:
	Graph();
	~Graph();
};

class GraphMatrix : Graph
{
	int** Matrix;
	void MarkVisitedRec(int i);

public:
	GraphMatrix(int size);
	~GraphMatrix();

	void GenerateRandom();
	std::string ToString();
	std::string ToStringCalc();
	bool CheckConnectivity();
};

class GraphStructure : Graph
{

	std::vector<int>* Structure;
public:
	GraphStructure(int size);
	~GraphStructure();

	void GenerateRandom();

	bool CheckConnectivity();
	void MarkVisitedRec(int vertex);
	std::string ToString();
};

#endif