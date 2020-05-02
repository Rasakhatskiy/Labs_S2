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
		Matrix[i] = new int[size];

}

GraphMatrix::~GraphMatrix()
{
	for (int i = 0; i < Size; ++i)
		delete[] Matrix[i];
	delete[] Matrix;
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

	for (int i = 0; i < Size; i++)
		if (Matrix[vertex][i])
			if (!Visited[i])
				subResult += DFS_MarkVisitedRec(i);

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

//--------------------------------------------------


GraphStructure::GraphStructure(int size)
{
	Size = size;
	Visited = new bool[size];
	Structure = new std::vector<int>[size];
}

GraphStructure::~GraphStructure()
{
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
					Structure[i].push_back(j);
	}
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
	for (int j = 0; j < Structure[vertex].size(); j++)
	{
		if (!Visited[Structure[vertex][j]])
			MarkVisitedRec(Structure[vertex][j]);
	}
}

std::string GraphStructure::DFS_MarkVisitedRec(int vertex)
{
	std::string subResult;
	Visited[vertex] = true;
	subResult += std::to_string(vertex) + " ";

	for (int j = 0; j < Structure[vertex].size(); j++)
		if (!Visited[Structure[vertex][j]])
				subResult += DFS_MarkVisitedRec(Structure[vertex][j]);
	return subResult;
}

//Depth-first search
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

std::string GraphStructure::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "->";
		for (auto& j : Structure[i])
		{
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

std::string GraphStructure::ToStringCalc()
{
	std::string result;
	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			result += std::to_string(i) + " " + std::to_string(j) + "\n";

	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}