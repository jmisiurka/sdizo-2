#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "Heap.h"
#include "AdjacencyList.h"
#include "Queue.h"

//Klasa reprezentująca macierz sąsiedztwa
class AdjacencyMatrix
{
    int V;                        //liczba wierzchołków grafu
    int** matrix;                       //macierz sąsiedztwa

public:
    AdjacencyMatrix(int V);
    ~AdjacencyMatrix();

    void loadFromFile(const std::string& filename, int problem, int* additionalValues);

    void loadFromAdjacencyList(const AdjacencyList& graph, int V);

    int& get(int vertexA, int vertexB) const;

    void print() const;

    void MST_Prim(int starting = 0);

    void MST_Kruskal();

    int Kruskal_parent(int vertex, int *parents);

    void Shortpath_Dijkstra(int starting);

    void Shortpath_BF(int starting);

    bool BFS(int start, int end, int* parents);

    bool DFS(int start, int end, int* parents);

    bool DFSVisit(int u, int end, char *color, int *parents);

    void Ford_Fulkerson(int start, int end, int pathfinding);
};

#endif