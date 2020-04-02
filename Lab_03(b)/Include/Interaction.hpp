#ifndef INTERACTION_HPP
#define INTERACTION_HPP
#include "../Include/Point.hpp"
#include "../Include/Message.hpp"
#include "../Include/Sort.hpp"
#include "../Include/RandomText.hpp"

#include <iostream>
#include <conio.h>
#include <vector>

//-------------this is for random-----------
#include<random>
#include<chrono>
//--------------------------------------------

extern std::default_random_engine randomEngine;
extern std::uniform_int_distribution<int> intRandomGenerator;

extern int SIZE_M_POINT;
extern Point3D* MOTHER_ARRAY_POINT;

extern int SIZE_M_MESSAGE;
extern Message* MOTHER_ARRAY_MESSAGE;

void PrintArray(Point3D* arr, int size);
void PrintArray(Message* arr, int size);
void PrintMessage(Message message);

void LaunchBenchmark();
void SilentShufflePoint3D(int size);
void ShuffleMessages();

void ShufflePoint3D();
void InsertionSortLaunch();
void QuickSortLaunch();
void MergeSortLaunch();


Message GetRandomMessage();
std::string GetRandomText();
std::string GetRandomAuthor();
std::string GetRandomRecipient();


#endif INTERACTION_HPP