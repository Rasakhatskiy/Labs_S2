#ifndef SORT_HPP
#define SORT_HPP
#include "../Include/Point.hpp"

void InsertionSort(Point3D arr[], int size)
{
	Point3D comparer;
	int i, j;
	for (i = 1; i < size; i++)
	{
		comparer = arr[i];
		j = i - 1;
		
		//if element is smaller than comparer, move it one position forward
		while (j >= 0 && arr[j] < comparer)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = comparer;
	}
}

#endif //INSERTION_SORT_HPP
