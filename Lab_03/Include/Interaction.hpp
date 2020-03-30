#ifndef INTERACTION_HPP
#define INTERACTION_HPP
#include "../Include/Point.hpp"
#include "../Include/Sort.hpp"

#include <iostream>
#include <conio.h>
#include <chrono>


//-------------this is for random-----------
#include <cstdlib> 
#include <ctime>
//--------------------------------------------

extern int SIZE;
extern Point3D* MOTHER_ARRAY;

void PrintArray(Point3D arr[], int size);

void LaunchBenchmark();
void SilentShuffle(int size);

void Shuffle();
void InsertionSortLaunch();
void QuickSortLaunch();
void MergeSortLaunch();



#endif INTERACTION_HPP