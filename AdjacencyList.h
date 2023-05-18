#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>

//struktura pojedynczego wpisu w liście sąsiedztwa zawierająca wskaźnik na
//kolejny element, numer przyłączonego wierzchołka i wagę krawędzi
struct AdjacencyListNode
{
    AdjacencyListNode* next;
    int adjacentVertex;
    int weight;
};

//klasa reprezentująca listę sąsiedztwa
class AdjacencyList
{
    const int V;
    AdjacencyListNode** list;
public:
    AdjacencyList(int V);
    ~AdjacencyList();

    int getWeight(int vertexA, int vertexB) const;

    void print() const;
};

#endif
