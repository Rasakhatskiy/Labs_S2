#ifndef INTERACTION_HPP
#define INTERACTION_HPP
#include <conio.h>
#include "FlawlessMenu.hpp"
#include "../Include/Graph.hpp"

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

#endif
