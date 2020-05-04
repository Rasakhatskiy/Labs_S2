#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <random>
#include <string>
#include <tuple>
#include <list>
#include <queue>
#include <stdexcept>
typedef std::tuple<int, int, bool> IIB;
typedef std::tuple<int, int, int> III;

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
		bool operator()(IIB const& lhs, IIB const& rhs) const
		{
			return std::get<1>(lhs) > std::get<1>(rhs);
		}
	};

	struct DisjointSets
	{
		int* Parents, * Ranks;
		int Size;
		DisjointSets(int size);
		int FindParent(int v);
		void MergeSet(int v, int w);
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

	int GetSumWeight();
	std::string ToString();
	std::string ToStringCalc();

	bool CheckConnectivity();

	std::string Dijkstra();
	int Dijkstra_MinDistance(int[], bool[]);

	std::string KahnsSort();

	int FindMin(int key[], bool mstSet[]);
	GraphMatrix* FindMST();
	GraphMatrix* KruskalMST();

	std::string DFS(bool);
};

class GraphStructure : Graph
{
	struct VertexRelation
	{
		int Vertex;
		int Weight;
		VertexRelation(int v, int w) : 
			Vertex(v), Weight(w) {}
	};

	std::vector<VertexRelation>* Structure;
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
	GraphStructure* KruskalMST();

	void AddEdge(int vertex1, int vertex2, int weight);

	std::string ToString();
	std::string ToStringCalc();
	int GetSumWeight();
};

#endif