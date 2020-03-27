#include "../Include/Point.hpp"
#include "../Include/Sort.hpp"
#include <iostream>

void PrintArray(Point3D arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "(" << arr[i].X << " " << arr[i].Y << " " << arr[i].Z << ")" << std::endl;
	}
	std::cout << std::endl;
}


int main()
{
	Point3D p0(1, 1, 1);
	Point3D p1(2, 3, 5);
	Point3D p2(2, 2, 4);
	Point3D p3(1, 3, 4);
	Point3D p4(1, 3, 5);
	Point3D p5(3, 1, 4);
	Point3D p6(1, 5, 9);
	Point3D p7(2, 6, 5);
	Point3D p8(7, 7, 7);
	Point3D p9(2, 2, 2);

	const int size = 10;

	std::cout << "Insertion sort" << std::endl;
	Point3D arr[size] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9};
	PrintArray(arr, size);
	InsertionSort(arr, 0, size - 1);
	PrintArray(arr, size);

	std::cout << "NesQuick sort" << std::endl;
	Point3D arr2[size] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 };
	PrintArray(arr2, size);
	QuickSort(arr2, 0, size - 1);
	PrintArray(arr2, size);

	std::cout << "Merge sort" << std::endl;
	Point3D arr3[size] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 };
	PrintArray(arr3, size);
	MergeSort(arr3, 0, size - 1);
	PrintArray(arr3, size);
}