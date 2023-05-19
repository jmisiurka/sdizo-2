#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "Heap.h"

//Klasa reprezentująca macierz sąsiedztwa
class AdjacencyMatrix
{
    int V;                        //liczba wierzchołków grafu
    int** matrix;                       //macierz sąsiedztwa

public:
    AdjacencyMatrix(int V);
    ~AdjacencyMatrix();

    void loadFromFile(const std::string& filename);

    int& get(int i, int j) const;

    void print() const;

    void MST_Prim(int starting = 0);
};

#endif