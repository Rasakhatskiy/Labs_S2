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




#endif //SORT_HPP
