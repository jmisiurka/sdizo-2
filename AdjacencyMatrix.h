#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "Heap.h"
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

    void generateRandomGraph(int graphV, bool directed, int minWeight, int maxWeight, int densityLevel);

    int get(int vertexA, int vertexB) const;

    int getV() const;

    void print() const;

    void MST_Prim(int starting = 0, bool test = false);

    void MST_Kruskal(bool test = false);

    int Kruskal_parent(int vertex, int *parents);

    void shortpath_Dijkstra(int starting, bool test = false);

    void shortpath_BF(int starting, bool test = false);

    bool BFS(int start, int end, int* parents);

    bool DFS(int start, int end, int* parents);

    bool DFSVisit(int u, int end, char *color, int *parents);

    void Ford_Fulkerson(int start, int end, int pathfinding, bool test = false);
};

#endif