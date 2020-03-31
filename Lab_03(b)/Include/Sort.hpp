#ifndef SORT_HPP
#define SORT_HPP
#include "../Include/Point.hpp"

//---------------------------------------INSERTION-------------------------------------
void InsertionSort(Point3D* arr, int lowest, int highest);

//---------------------------------------QUICK SORT------------------------------------
int FindPartitionIndex(Point3D* arr, int lowest, int highest);
void QuickSort(Point3D* arr, int lowest, int highest);

//--------------------------------------MERGE SORT------------------------------------
void Merge(Point3D* arr, int lowest, int middle, int highest);
void MergeSort(Point3D* arr, int lowest, int highest);

#endif //SORT_HPP
