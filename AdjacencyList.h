#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>
#include <fstream>

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
    int V;
    AdjacencyListNode** list;
public:
    AdjacencyList(int V);
    ~AdjacencyList();

    void loadFromFile(const std::string& filename, int problem, int* additionalValues);

    int get(int vertexA, int vertexB) const;

    void clearList();

    void print() const;

    int countTotalWeight();

    void MST_Prim(int starting = 0);

    void MST_Kruskal();

    int Kruskal_parent(int vertex, int* parents);

    void Shortpath_Dijkstra(int starting);

    void Shortpath_BF(int starting);
};

#endif
