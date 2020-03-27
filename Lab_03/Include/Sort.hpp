#ifndef SORT_HPP
#define SORT_HPP
#include "../Include/Point.hpp"
//---------------------------------------INSERTION-------------------------------------


void InsertionSort(Point3D arr[], int lowest, int highest)
{
	Point3D comparer;
	int i, j;
	for (i = lowest + 1; i <= highest; i++)
	{
		comparer = arr[i];
		j = i - 1;
		
		//if element is smaller than comparer, move it one position forward
		while (j >= lowest && arr[j] < comparer)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = comparer;
	}
}

//---------------------------------------QUICK SORT------------------------------------

int FindPartitionIndex(Point3D arr[], int lowest, int highest)
{
	Point3D pivot = arr[lowest];
	int i = lowest - 1;
	int j = highest + 1;

	while (true)
	{
		//find index before leftmost >= pivot 
		do i++;
		while (arr[i] > pivot);

		//find index before rightmost <= pivot
		do j--;
		while (arr[j] < pivot);

		//if indexes are the same return it 
		if (i >= j) return j;

		//else swap it
		Point3D temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}

//Несквик сорт за спаданням
void QuickSort(Point3D arr[], int lowest, int highest)
{
	if (lowest < highest)
	{
		int partitionIndex = FindPartitionIndex(arr, lowest, highest);

		//sort part of array before partition index
		QuickSort(arr, lowest, partitionIndex);

		//sort part of array after partition index
		QuickSort(arr, partitionIndex + 1, highest);
	}
}


//--------------------------------------MERGE SORT------------------------------------
void Merge(Point3D arr[], int lowest, int middle, int highest)
{
	int i, j, k;
	int sizeFirst = middle - lowest + 1;
	int sizeSecond = highest - middle;


	Point3D* tempFirst = new Point3D[sizeFirst];
	Point3D* tempSecond = new Point3D[sizeSecond];

	
	//split data between arrays
	for (i = 0; i < sizeFirst; i++)
		tempFirst[i] = arr[lowest + i];

	for (j = 0; j < sizeSecond; j++)
		tempSecond[j] = arr[middle + 1 + j];


	i = 0; //start index of tempFirst array 
	j = 0; //start index of tempSecond array 
	k = lowest; //start index of merged array 


	//merge
	while (i < sizeFirst && j < sizeSecond)
	{
		if (tempFirst[i] >= tempSecond[j])
		{
			arr[k] = tempFirst[i];
			i++;
		}
		else
		{
			arr[k] = tempSecond[j];
			j++;
		}
		k++;
	}


	//get extra elements from first array
	while (i < sizeFirst)
	{
		arr[k] = tempFirst[i];
		i++;
		k++;
	}


	//get extra elements from second array
	while (j < sizeSecond)
	{
		arr[k] = tempSecond[j];
		j++;
		k++;
	}

	delete[] tempFirst;
	delete[] tempSecond;
}

void MergeSort(Point3D arr[], int lowest, int highest)
{
	if (lowest < highest)
	{
		int middle = (lowest + highest) / 2;

		MergeSort(arr, lowest, middle);
		MergeSort(arr, middle + 1, highest);

		Merge(arr, lowest, middle, highest);
	}
}

#endif //SORT_HPP
