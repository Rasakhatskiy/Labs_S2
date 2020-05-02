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
		result += std::to_string(i) + "-";
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[i][j])
				result += std::to_string(j) + "-";
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

std::string GraphStructure::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "-";
		for (auto& j : Structure[i])
		{
			result += std::to_string(j) + "-";
		}
		result += "\n";
	}
	if (CheckConnectivity())
		result += "Connected";
	else
		result += "Not connected";
	return result;
}
