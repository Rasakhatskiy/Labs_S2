#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <random>
#include <string>
#include <tuple>
#include <list>
#include <queue>

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

	struct CustomBiggerThan
	{
		bool operator()(std::tuple<int, int, bool> const& lhs, std::tuple<int, int, bool> const& rhs) const
		{
			return std::get<1>(lhs) > std::get<1>(rhs);
		}
	};

public:
	Graph();
	~Graph();
};

class GraphMatrix : Graph
{
	int** Matrix;
	void MarkVisitedRec(int);
	std::string DFS_MarkVisitedRec(int);
	std::string DFS_MarkVisitedRec_Weight(int);
public:
	GraphMatrix(int size);
	~GraphMatrix();

	void AddEdge(int vertex1, int vertex2, int weight);

	void GenerateRandom();
	std::string ToString();
	std::string ToStringCalc();

	bool CheckConnectivity();

	std::string Dijkstra();
	int Dijkstra_MinDistance(int[], bool[]);

	std::string KahnsSort();

	int FindMin(int key[], bool mstSet[]);
	GraphMatrix* FindMST();

	std::string DFS(bool);
};

class GraphStructure : Graph
{

	std::vector<int>* Structure;
	std::string DFS_MarkVisitedRec(int);
	void MarkVisitedRec(int);
	int FindMin(int keys[], bool notUsed[]);
public:
	GraphStructure(int size);
	~GraphStructure();

	void GenerateRandom();

	bool CheckConnectivity();
	std::string DFS();

	std::string KahnsSort();

	GraphStructure* FindMST();

	void AddEdge(int vertex1, int vertex2);

	std::string ToString();
	std::string ToStringCalc();
};

#endif