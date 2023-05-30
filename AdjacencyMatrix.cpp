#include <climits>
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const int V) : V(V)
{
    matrix = new int *[V];                           //alokacja 1 wymiaru tablicy
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];                     //alokacja 2 wymiaru tablicy i wyzerowanie wszystkich komórek
        for (int j = 0; j < V; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    for (int i = 0; i < V; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void AdjacencyMatrix::loadFromFile(const std::string &filename, bool directed)
{
    std::ifstream filestream(filename);

    if (!filestream.is_open())
    {
        std::cout << "Błąd podczas otwierania pliku" << std::endl;
        return;
    }

    int numberOfEdges, numberOfVertices;
    filestream >> numberOfEdges;
    filestream >> numberOfVertices;

    for (int i = 0; i < V; i++)                     //usunięcie dotychczasowej macierzy
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    V = numberOfVertices;

    matrix = new int *[V];                           //alokacja 1 wymiaru tablicy
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];                     //alokacja 2 wymiaru tablicy i wyzerowanie wszystkich komórek
        for (int j = 0; j < V; j++)
        {
            matrix[i][j] = 0;
        }
    }

    int vertexA, vertexB, weight;
    for (int i = 0; i < numberOfEdges; i++)
    {
        filestream >> vertexA;
        filestream >> vertexB;
        filestream >> weight;

        matrix[vertexA][vertexB] = weight;
        if (!directed)
        {
            matrix[vertexB][vertexA] = weight;
        }
    }

    filestream.close();
}

int &AdjacencyMatrix::get(int vertexA, int vertexB) const
{
    return matrix[vertexA][vertexB];
}

void AdjacencyMatrix::print() const
{
    printf("    |");
    for (int i = 0; i < V - 1; i++)
    {
        printf("%-4d|", i);
    }
    printf("%-4d\n", V - 1);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("-----");
        }
        printf("\n");
        printf("%-4d|", i);
        for (int j = 0; j < V - 1; j++)
        {
            printf("%-4d|", matrix[i][j]);
        }
        printf("%-4d\n", matrix[i][V - 1]);
    }
    std::cout << std::endl << std::endl;
}

int AdjacencyMatrix::countTotalWeight()
{
    int sum = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = i; j < V; j++)
        {
            sum += matrix[i][j];
        }
    }
    return sum;
}

void AdjacencyMatrix::MST_Prim(int starting)
{
    AdjacencyMatrix mst = AdjacencyMatrix(V);

    KeyPrevPair vertices[V];                //tablica wszystkich wierzchołków
    bool considered[V];                     //tablica rozpatrzonych wierzchołków

    Heap Q = Heap<KeyPrevPair *>(V);
    //to może mieć wpływ na złożoność
    for (int i = 0; i < V; i++)             //przypisanie numerów wierzchołków (póki co wszystkie elementy takie same)
    {
        vertices[i].id = i;
        Q.add(&vertices[i]);
        considered[i] = false;
    }

    int u = starting;

    vertices[u].key = 0;                    //wierzchołek początkowy ma na start klucz 0
    Q.heapify();                           //naprawa kopca

    while (!Q.empty())
    {
        u = Q.popRoot()->id;                //pobranie elementu z kolejki

        for (int i = 0; i < V; i++)
        {
            if (matrix[u][i] != 0)          //wywoływane dla wszystkich sąsiadów <u>
            {
                if (!considered[i] && vertices[i].key > matrix[u][i])
                {
                    vertices[i].key = matrix[u][i];
                    vertices[i].previous = u;
                    Q.heapify();
                }
            }
        }
        considered[u] = true;
    }

    int sum = 0;
    for (KeyPrevPair pair: vertices)
    {
        int vertexA = pair.id;
        int vertexB = pair.previous;
        if (vertexB != -1)
        {
            sum += matrix[vertexA][vertexB];
            mst.matrix[vertexA][vertexB] = matrix[vertexA][vertexB];
            mst.matrix[vertexB][vertexA] = matrix[vertexB][vertexA];
        }
    }

    mst.print();
    std::cout << "Suma wag krawędzi:" << sum << std::endl << std::endl;
}

void AdjacencyMatrix::MST_Kruskal()
{
    Edge mstEdges[V - 1];                           //V - 1 krawędzi w MST
    Edge allEdges[V * (V - 1) / 2];                 //max krawędzi w grafie: V * (V - 1) / 2
    Heap Q = Heap<Edge *>(
            V * (V - 1) / 2);      //kopiec operuje na wskaźnikach, więc tablica wyżej jest trochę sztuczna

    int edgeCount = 0;

    for (int i = 0; i < V; i++)                     //kolejka krawędzi posortowana rosnąco
    {
        for (int j = i; j < V; j++)
        {
            if (matrix[i][j] != 0)
            {
                Edge edge = Edge();
                edge.weight = matrix[i][j];
                edge.vertexA = i;
                edge.vertexB = j;
                allEdges[edgeCount] = edge;
                Q.add(&(allEdges[edgeCount]));
                edgeCount++;
            }
        }
    }

    Q.fixDown(0);

    int parent[V];

    for (int i = 0; i < V; i++)                     //poddrzewa rozłączne dla każdego wierzchołka
    {
        parent[i] = i;
    }

    int mstCount = 0;

    while (!Q.empty())
    {
        Edge edge = *(Q.popRoot());

        int parentA = Kruskal_parent(edge.vertexA, parent);
        int parentB = Kruskal_parent(edge.vertexB, parent);

        if (parentA != parentB)
        {
            mstEdges[mstCount] = edge;
            mstCount++;
            parent[parent[edge.vertexB]] = parentA;
        }
    }

    int sum = 0;
    for (Edge edge : mstEdges)
    {
        sum += edge.weight;
        std::cout << "(" << edge.vertexA << " - " << edge.vertexB << ", " << edge.weight << ")" << std::endl;
    }
    std::cout << "Suma wag krawędzi: " << sum << std::endl;
}

int AdjacencyMatrix::Kruskal_parent(int vertex, int *parents)
{
    if (parents[vertex] != vertex)
    {
        parents[vertex] = Kruskal_parent(parents[vertex], parents);
    }
    return parents[vertex];
}
