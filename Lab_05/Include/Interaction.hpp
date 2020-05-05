#ifndef INTERACTION_HPP
#define INTERACTION_HPP
#include <conio.h>
#include <chrono>
#include <thread>
#include "FlawlessMenu.hpp"
#include "../Include/Graph.hpp"

const unsigned int microseconds = 3000;
extern Graph* graph;
extern bool IsMatrix;

void Demo();
void Benchmark();

void FillMatrixRandom();
void FillMatrixByHand();
void FillStructureRandom();
void FillStructureByHand();

void CheckConnectivity();
void DFSA();
void DFSS();
void Dijkstra();
void KahnsSort();
void FindMST();
void KruskalMST();

void ShowGraph();

int ReadSize();
char ReadChar();
int ReadVertex();
int ReadWeight();

void Sleep();

double DoSomething(std::string something, void (*task)(void));

void Bench_CheckConnectivity();
void Bench_DFSA();
void Bench_DFSS();
void Bench_Dijkstra();
void Bench_KahnsSort();
void Bench_FindMST();
void Bench_KruskalMST();

void DuHast(bool& flag, int a, int max);
#endif
