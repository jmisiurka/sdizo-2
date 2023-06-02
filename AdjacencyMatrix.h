#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "Heap.h"
#include "AdjacencyList.h"

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

    int countTotalWeight();

    void MST_Prim(int starting = 0);

    void MST_Kruskal();

    int Kruskal_parent(int vertex, int *parents);

    void Shortpath_Dijkstra(int starting);

    void Shortpath_BF(int starting);
};

#endif