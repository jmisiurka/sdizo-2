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

void AdjacencyMatrix::loadFromFile(const std::string& filename)
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
        matrix[vertexB][vertexA] = weight;
    }

    filestream.close();
}

int& AdjacencyMatrix::get(int vertexA, int vertexB) const
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

AdjacencyMatrix AdjacencyMatrix::MST_Prim(int starting)
{
    AdjacencyMatrix mst = AdjacencyMatrix(V);

    KeyPrevPair vertices[V];                //tablica wszystkich wierzchołków
    bool considered[V];                     //tablica rozpatrzonych wierzchołków

    Heap Q = Heap<KeyPrevPair*>(V);
    //to może mieć wpływ na złożoność
    for (int i = 0; i < V; i++)             //przypisanie numerów wierzchołków (póki co wszystkie elementy takie same)
    {
        vertices[i].id = i;
        Q.add(&vertices[i]);
        considered[i] = false;
    }

    int u = starting;

    vertices[u].key = 0;                    //wierzchołek początkowy ma na start klucz 0
    Q.fixDown(0);                     //naprawa całego kopca

    while (!Q.empty())
    {
        u = Q.popRoot()->id;                //pobranie elementu z kolejki

        for(int i = 0; i < V; i++)
        {
            if (matrix[u][i] != 0)          //wywoływane dla wszystkich sąsiadów <u>
            {
                if (!considered[i] && vertices[i].key > vertices[u].key + matrix[u][i])
                {
                    vertices[i].key = vertices[u].key + matrix[u][i];
                    vertices[i].previous = u;
                }
            }
        }
    }

    for (KeyPrevPair pair : vertices)
    {
        int vertexA = pair.id;
        int vertexB = pair.previous;
        mst.matrix[vertexA][vertexB] = matrix[vertexA][vertexB];
        mst.matrix[vertexB][vertexA] = matrix[vertexB][vertexA];
    }

    return mst;
}
