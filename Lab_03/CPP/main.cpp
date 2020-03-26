#include "../Include/Point.hpp"
#include "../Include/Sort.hpp"
#include <iostream>

void PrintArray(Point3D arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "(" << arr[i].X << " " << arr[i].Y << " " << arr[i].Z << ")" << std::endl;
	}
}


int main()
{
	Point3D p1(1, 2, 3);
	Point3D p2(1, 2, 4);
	Point3D p3(1, 3, 4);
	Point3D p4(1, 3, 5);

	Point3D arr[8];
	arr[0] = p1;
	arr[1] = p4;
	arr[2] = p3;
	arr[3] = p2;

	InsertionSort(arr, 4);

	p1 = p2;
	p2 = p3;
}