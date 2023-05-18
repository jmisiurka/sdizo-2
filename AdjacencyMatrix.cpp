#include <climits>
#include "AdjacencyMatrix.h"

//struktury pomocnicze
struct KeyParentPair
{
    int key = INT_MAX;
    int parent = -1;
};




//metody klasy AdjacencyMatrix
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

int &AdjacencyMatrix::get(int i, int j) const
{
    return matrix[i][j];
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
}

void AdjacencyMatrix::MST_Prim(int starting)
{
    KeyParentPair vertices[V];

    Heap Q = Heap(V / 2 * (V - 1));     //kolejka priorytetowa - kopiec o max V/2*(V+1) elementach


}
