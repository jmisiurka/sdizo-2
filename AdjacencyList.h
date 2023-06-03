#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <iostream>
#include <fstream>
#include "Queue.h"

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

    void generateRandomGraph(int graphV, bool directed, int minWeight, int maxWeight, int density);

    AdjacencyListNode* getNode(int i) const;

    int get(int vertexA, int vertexB) const;

    void removeEdge(int i, int j);

    void clearList();

    void print() const;

    void MST_Prim(int starting = 0);

    void MST_Kruskal();

    int Kruskal_parent(int vertex, int* parents);

    void Shortpath_Dijkstra(int starting);

    void Shortpath_BF(int starting);

    bool BFS(AdjacencyList &graph, int start, int end, int *parents);

    bool DFS(AdjacencyList &graph, int start, int end, int *parents);

    void DFSVisit(AdjacencyList &graph, int u, char *color, int *parents);

    void Ford_Fulkerson(int start, int end, int pathfinding);
};

#endif
