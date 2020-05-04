#include "../Include/Graph.hpp"
/*
 * Directional graph
*/


Graph::Graph()
{
	RandomGenerator = std::mt19937(RandomDevice());
	RandomDistributorInt = std::uniform_int_distribution<int>(1, 47);
	RandomDistributorBool = std::uniform_int_distribution<int>(0, 1);
}
Graph::~Graph(){}

int Graph::GetSize()
{
	return Size;
}

int Graph::GetRandomInt()
{
	return RandomDistributorInt(RandomGenerator);
}

bool Graph::GetRandomBool()
{
	int kal = RandomDistributorBool(RandomGenerator);
	return kal;
}


//-------------------------------------------------


GraphMatrix::GraphMatrix(int size)
{
	Size = size;
	Visited = new bool[size];
	Matrix = new int* [size];
	for (int i = 0; i < size; ++i)
	{
		Matrix[i] = new int[size];
		for (int j = 0; j < Size; j++)
		{
			Matrix[i][j] = 0;
		}
	}
}

GraphMatrix::~GraphMatrix()
{
	for (int i = 0; i < Size; ++i)
		delete[] Matrix[i];
	delete[] Matrix;
}

void GraphMatrix::AddEdge(int vertex1, int vertex2, int weight)
{
	if (vertex1 >= Size || vertex2 >= Size || weight < 0)
		throw std::out_of_range("Invalid user exception");
	Matrix[vertex1][vertex2] = weight;
}

void GraphMatrix::GenerateRandom()
{
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			if (i == j)
				Matrix[i][j] = 0;
			else
				if (GetRandomBool())
					Matrix[i][j] = GetRandomInt();
				else
					Matrix[i][j] = 0;
}

bool GraphMatrix::CheckConnectivity()
{
	for (int i = 0; i < Size; i++) 
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;

		MarkVisitedRec(i);

		for (int j = 0; j < Size; j++)
			if (!Visited[j])
				return false;
	}
	return true;
}

int GraphMatrix::GetSumWeight()
{
	int sum = 0;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			sum += Matrix[i][j];
		}
	}
	return sum;
}

void GraphMatrix::MarkVisitedRec(int vertex)
{
	Visited[vertex] = true;
	for (int j = 0; j < Size; j++) 
	{
		if (Matrix[vertex][j])
		{
			if (!Visited[j])
				MarkVisitedRec(j);
		}
	}
}



std::string GraphMatrix::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "->";
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[i][j])
				result += std::to_string(j) + "->";
		}
		result += "\n";
	}
	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}

std::string GraphMatrix::ToStringCalc()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[i][j])
				result += std::to_string(i) + " " + std::to_string(j) + "\n";
		}
		//result += "\n";
	}
	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}



std::string GraphMatrix::DFS_MarkVisitedRec(int vertex) 
{
	std::string subResult;
	Visited[vertex] = true;
	subResult += std::to_string(vertex) + " ";

	for (int j = 0; j < Size; j++)
		if (Matrix[vertex][j])
			if (!Visited[j])
				subResult += DFS_MarkVisitedRec(j);

	return subResult;
}

std::string GraphMatrix::DFS_MarkVisitedRec_Weight(int vertex)
{
	std::string subResult;
	Visited[vertex] = true;
	subResult += std::to_string(vertex) + " ";

	std::vector<std::tuple<int, int, bool>> vect;
	for (int i = 0; i < Size; i++)
		vect.push_back(std::tuple<int, int, bool>(i, Matrix[vertex][i], Visited[i]));
	std::sort(vect.begin(), vect.end(), CustomBiggerThan());

	for (int i = 0; i < Size; i++)
		if (std::get<1>(vect[i]) && !std::get<2>(vect[i]))
			subResult += DFS_MarkVisitedRec(std::get<0>(vect[i]));

	return subResult;
}

std::string GraphMatrix::DFS(bool weight = false)
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;
		if (weight)
			result += DFS_MarkVisitedRec_Weight(i) + "\n";
		else
			result += DFS_MarkVisitedRec(i) + "\n";
	}
	return result;
}



int GraphMatrix::Dijkstra_MinDistance(int result[], bool shortestPathIncludance[])
{
	int minVal = INT_MAX;
	int minId = -1;
	for (int i = 0; i < Size; i++)
	{
		if (shortestPathIncludance[i] == false &&
			result[i] <= minVal)
		{
			minVal = result[i];
			minId = i;
		}
	}
	return minId;
}

std::string GraphMatrix::Dijkstra()
{
	int* result = new int[Size];
	bool* shortestPathIncludance = new bool[Size];

	std::string resultStr;

	for (int from = 0; from < Size; from++)
	{
		for (int i = 0; i < Size; i++)
		{
			result[i] = INT_MAX;
			shortestPathIncludance[i] = false;
		}
		result[from] = 0;
		for (int i = 0; i < Size - 1; i++)
		{
			int minId = Dijkstra_MinDistance(result, shortestPathIncludance);
			shortestPathIncludance[minId] = true;
			for (int j = 0; j < Size; j++)
			{
				if (!shortestPathIncludance[j] &&
					Matrix[minId][j] &&
					result[minId] != INT_MAX &&
					result[minId] + Matrix[minId][j] < result[j])
				{
					result[j] = result[minId] + Matrix[minId][j];
				}
			}
		}
		for (int i = 0; i < Size; i++)
		{
			resultStr +=
				"From " + std::to_string(from) +
				" to " + std::to_string(i) +
				" = " + std::to_string(result[i]) + "\n";
		}
		resultStr += "\n";
	}
	return resultStr;
}



std::string GraphMatrix::KahnsSort()
{
	std::vector<int> degree(Size, 0);

	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			if(Matrix[i][j])
				degree[j]++;

	std::queue<int> queue;
	for (int i = 0; i < Size; i++)
		if (!degree[i])
			queue.push(i);

	int visitedVerts = 0;
	std::vector <int> result;

	while (!queue.empty())
	{
		int i = queue.front();
		queue.pop();
		result.push_back(i);

		for (int j = 0; j < Size; j++)
			if (!--degree[j])
				queue.push(j);

		visitedVerts++;
	}

	if (visitedVerts != Size)
		return "Impossible to sort with Kahn's method, this is cycle graph.";
	
	std::string resultStr;
	for (int i = 0; i < result.size(); i++)
		resultStr += std::to_string(result[i])  + " ";
	return resultStr;
}



int GraphMatrix::FindMin(int keys[], bool notUsed[])
{
	int min = INT_MAX;
	int minId = -1;
	for (int i = 0; i < Size; i++)
	{
		if (notUsed[i] == false && keys[i] < min)
		{
			min = keys[i];
			minId = i;
		}
	}
	return minId;
}

GraphMatrix* GraphMatrix::FindMST()
{
	int* result = new int[Size];
	int* keys = new int[Size];
	bool* notUsed = new bool[Size];

	for (int i = 0; i < Size; i++)
	{
		keys[i] = INT_MAX;
		notUsed[i] = false;
	}

	keys[0] = 0;
	result[0] = -1;

	for (int i = 0; i < Size - 1; i++)
	{
		int min = FindMin(keys, notUsed);
		notUsed[min] = true;
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[min][j] &&
				!notUsed[j] &&
				Matrix[min][j] < keys[j])
			{
				result[j] = min;
				keys[j] = Matrix[min][j];
			}
		}
	}


	GraphMatrix* resultGraph = new GraphMatrix(Size);
	for (int i = 1; i < Size; i++)
		resultGraph->AddEdge(result[i], i, Matrix[i][result[i]]);

	auto shit = resultGraph->ToString();


	return resultGraph;
}

GraphMatrix* GraphMatrix::KruskalMST()
{
	GraphMatrix* result = new GraphMatrix(Size);
	std::vector<III> edges;
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			edges.push_back(III(i, j, Matrix[i][j]));
	std::sort(edges.begin(), edges.end());

	int totalWeight = 0;
	DisjointSets disjointSets(Size);
	for (auto &i : edges)
	{
		int vertex_1 = std::get<0>(i);
		int vertex_2 = std::get<1>(i);
		int weight   = std::get<2>(i);

		int set_1 = disjointSets.FindParent(vertex_1);
		int set_2 = disjointSets.FindParent(vertex_2);
		if (set_1 != set_2)
		{
			result->AddEdge(vertex_1, vertex_2, weight);
			disjointSets.MergeSet(set_1, set_2);
			totalWeight += weight;
		}
	}
	return result;
}



GraphStructure::GraphStructure(int size)
{
	Size = size;
	Visited = new bool[size];
	Structure = new std::vector<VertexRelation>[size];
}

GraphStructure::~GraphStructure()
{
}

void GraphStructure::AddEdge(int vertex1, int vertex2, int weight)
{
	Structure[vertex1].push_back(VertexRelation(vertex2, weight));
}

void GraphStructure::GenerateRandom()
{
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			if (i == j)
				continue;
			else
				if (GetRandomBool())
					Structure[i].push_back(VertexRelation(j, GetRandomInt()));
	}
}

int GraphStructure::GetSumWeight()
{
	int sum = 0;
	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			sum += j.Weight;
	return sum;
}


bool GraphStructure::CheckConnectivity()
{
	for (int i = 0; i < Size; i++)
	{
		Visited[i] = false;
		MarkVisitedRec(i);
		for (int i = 0; i < Size; i++)
		{
			if (!Visited[i])
				return false;
		}
	}
	return true;
}

void GraphStructure::MarkVisitedRec(int vertex)
{
	Visited[vertex] = true;
	for (auto &j : Structure[vertex])
		if (!Visited[j.Vertex])
			MarkVisitedRec(j.Vertex);
}



std::string GraphStructure::DFS_MarkVisitedRec(int vertex)
{
	std::string subResult;
	Visited[vertex] = true;
subResult += std::to_string(vertex) + " ";

for (auto &j : Structure[vertex])
	if (!Visited[j.Vertex])
		subResult += DFS_MarkVisitedRec(j.Vertex);
return subResult;
}

std::string GraphStructure::DFS()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;
		result += DFS_MarkVisitedRec(i) + "\n";
	}
	return result;
}



std::string GraphStructure::KahnsSort()
{
	std::vector<int> degree(Size, 0);

	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			degree[j.Vertex]++;

	std::queue<int> queue;
	for (int i = 0; i < Size; i++)
		if (!degree[i])
			queue.push(i);

	int visitedVerts = 0;
	std::vector <int> result;

	while (!queue.empty())
	{
		int i = queue.front();
		queue.pop();
		result.push_back(i);

		for (int j = 0; j < Size; j++)
			if (!--degree[j])
				queue.push(j);

		visitedVerts++;
	}

	if (visitedVerts != Size)
		return "Impossible to sort with Kahn's method, this is cycle graph.";

	std::string resultStr;
	for (int i = 0; i < result.size(); i++)
		resultStr += std::to_string(result[i]) + " ";
	return resultStr;
}



int GraphStructure::FindMin(int keys[], bool notUsed[])
{
	int min = INT_MAX;
	int minId = -1;
	for (int i = 0; i < Size; i++)
	{
		if (notUsed[i] == false && keys[i] < min)
		{
			min = keys[i];
			minId = i;
		}
	}
	return minId;
}

GraphStructure* GraphStructure::FindMST()
{
	int* result = new int[Size];
	int* keys = new int[Size];
	bool* notUsed = new bool[Size];

	for (int i = 0; i < Size; i++)
	{
		keys[i] = INT_MAX;
		notUsed[i] = false;
	}

	keys[0] = 0;
	result[0] = -1;

	for (int i = 0; i < Size - 1; i++)
	{
		int min = FindMin(keys, notUsed);
		notUsed[min] = true;

		for (auto& j : Structure[min])
		{
			if (j.Weight &&
				!notUsed[j.Vertex] &&
				j.Weight < keys[j.Vertex])
			{
				result[j.Vertex] = min;
				keys[j.Vertex] = j.Weight;
			}
		}
	}


	GraphStructure* resultGraph = new GraphStructure(Size);
	for (int i = 1; i < Size; i++)
	{
		for (auto& j : Structure[i])
		{
			if (j.Vertex == result[i])
			{
				resultGraph->AddEdge(result[i], i, j.Weight);
				break;
			}
		}
	}
	return resultGraph;
}

GraphStructure* GraphStructure::KruskalMST()
{
	GraphStructure* result = new GraphStructure(Size);
	std::vector<III> edges;
	for (int i = 0; i < Size; i++)
		for (auto &j : Structure[i])
			edges.push_back(III(i, j.Vertex, j.Weight));
	std::sort(edges.begin(), edges.end());

	int totalWeight = 0;
	DisjointSets disjointSets(Size);
	for (auto& i : edges)
	{
		int vertex_1 = std::get<0>(i);
		int vertex_2 = std::get<1>(i);
		int weight   = std::get<2>(i);

		int set_1 = disjointSets.FindParent(vertex_1);
		int set_2 = disjointSets.FindParent(vertex_2);
		if (set_1 != set_2)
		{
			result->AddEdge(vertex_1, vertex_2, weight);
			disjointSets.MergeSet(set_1, set_2);
			totalWeight += weight;
		}
	}
	return result;
}



std::string GraphStructure::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "->";
		for (auto& j : Structure[i])
		{
			result += std::to_string(j.Vertex) + "->";
		}
		result += "\n";
	}
	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}

std::string GraphStructure::ToStringCalc()
{
	std::string result;
	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			result += std::to_string(i) + " " + std::to_string(j.Vertex) + "\n";

	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}

//--------------------------------------------------

Graph::DisjointSets::DisjointSets(int size)
{
	Size = size;
	Parents = new int[size + 1];
	Ranks = new int[size + 1];
	for (int i = 0; i <= size; i++)
	{
		Ranks[i] = 0;
		Parents[i] = i;
	}
}

int Graph::DisjointSets::FindParent(int vertex)
{
	if (vertex != Parents[vertex])
		Parents[vertex] = FindParent(Parents[vertex]);
	return Parents[vertex];
}

void Graph::DisjointSets::MergeSet(int vertex_1, int vertex_2)
{
	vertex_1 = FindParent(vertex_1), vertex_2 = FindParent(vertex_2);
	if (Ranks[vertex_1] > Ranks[vertex_2])
		Parents[vertex_2] = vertex_1;
	else
		Parents[vertex_1] = vertex_2;
	if (Ranks[vertex_1] == Ranks[vertex_2])
		Ranks[vertex_2]++;
}