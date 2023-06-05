#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>
#include <fstream>
#include "Queue.h"
#include "AdjacencyMatrix.h"

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

    void copyFromMatrix(AdjacencyMatrix &graph);

    AdjacencyListNode* getNode(int i) const;

    int get(int vertexA, int vertexB) const;

    void removeEdge(int i, int j);

    void clearList();

    void print() const;

    void MST_Prim(int starting = 0, bool test = false);

    void MST_Kruskal(bool test = false);

    int Kruskal_parent(int vertex, int* parents);

    void shortpath_Dijkstra(int starting, bool test = false);

    void shortpath_BF(int starting, bool test = false);

    bool BFS(int start, int end, int *parents);

    bool DFS(int start, int end, int *parents);

    bool DFSVisit(int u, int end, char *color, int *parents);

    void Ford_Fulkerson(int start, int end, int pathfinding, bool test = false);
};

#endif
