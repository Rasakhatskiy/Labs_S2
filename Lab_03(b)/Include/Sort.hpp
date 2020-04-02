#ifndef SORT_HPP
#define SORT_HPP
#include "../Include/Point.hpp"
#include "../Include/Message.hpp"


//---------------------------------------COMPARATOR------------------------------------
extern std::string SortingOrder;

struct Point3D_BiggerThan_comparator
{
	inline bool operator()(const Point3D& struct1, const Point3D& struct2);
};

struct Message_smallerID_comparator
{
	inline bool operator()(const Message& struct1, const Message& struct2);
};

struct Message_smallerType_comparator
{
	inline bool operator()(const Message& struct1, const Message& struct2);
};

//---------------------------------------INSERTION-------------------------------------
void InsertionSort(Point3D* arr, int lowest, int highest);

//---------------------------------------QUICK SORT------------------------------------
int FindPartitionIndex(Point3D* arr, int lowest, int highest);
void QuickSort(Point3D* arr, int lowest, int highest);

//--------------------------------------MERGE SORT------------------------------------
void Merge(Point3D* arr, int lowest, int middle, int highest);
void MergeSort(Point3D* arr, int lowest, int highest);

//--------------------------------------COUNTING SORT---------------------------------
void CountSort(Message* arr, int size);


//--------------------------------------RADIX SORT------------------------------------
int FindMaxID(Message* arr, int size);
void ExpSort(Message* arr, int size, int exp);
void RadixSort(Message* arr, int size);



#endif //SORT_HPP
