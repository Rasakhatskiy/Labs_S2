#ifndef SORT_HPP
#define SORT_HPP
#include "../Include/Point.hpp"
#include "../Include/Message.hpp"

//---------------------------------------INSERTION-------------------------------------
void InsertionSort(Point3D* arr, int lowest, int highest);

//---------------------------------------QUICK SORT------------------------------------
int FindPartitionIndex(Point3D* arr, int lowest, int highest);
void QuickSort(Point3D* arr, int lowest, int highest);

//--------------------------------------MERGE SORT------------------------------------
void Merge(Point3D* arr, int lowest, int middle, int highest);
void MergeSort(Point3D* arr, int lowest, int highest);

//--------------------------------------COUNTING SORT---------------------------------



//--------------------------------------RADIX SORT------------------------------------
// A utility function to get maximum value in arr[] 
int FindMaxID(Message* arr, int size)
{
	int max = arr[0].ID;
	for (int i = 1; i < size; i++)
		if (arr[i].ID > max)
			max = arr[i].ID;
	return max;
}

// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void ExpSort(Message * arr, int size, int exp)
{
	Message* result = new Message[size];
	int i, count[10] = { 0 };

	for (i = 0; i < size; i++)
		count[(arr[i].ID / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = size - 1; i >= 0; i--)
	{
		result[count[(arr[i].ID / exp) % 10] - 1] = arr[i];
		count[(arr[i].ID / exp) % 10]--;
	}

	for (i = 0; i < size; i++)
		arr[i] = result[i];
}




#endif //SORT_HPP
