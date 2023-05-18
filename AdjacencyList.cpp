#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int V) : V(V)
{
    list = new AdjacencyListNode *[V];                   //alokacja pamięci pod listy
}

AdjacencyList::~AdjacencyList()
{
    for (int i = 0; i < V; i++)                         //iteracja po wszystkich listach
    {
        AdjacencyListNode *temp = list[i];
        while (temp != nullptr)                         //usunięcie kolejnych elementów list
        {
            AdjacencyListNode *next = temp->next;
            delete temp;
            temp = next;
        }
    }

    delete[] list;                                      //usunięcie pamięci tablicy list
}

int AdjacencyList::getWeight(int vertexA, int vertexB) const
{
    AdjacencyListNode *temp = list[vertexA];
    while (temp != nullptr)
    {
        if (temp->adjacentVertex == vertexB)            //krawędź łącząca A i B
        {
            return temp->weight;
        }
    }

    return 0;                                           //brak krawędzi łączącej A i B
}

void AdjacencyList::print() const
{
    for (int i = 0; i < V; i++)
    {
        AdjacencyListNode* temp = list[i];
        while (temp != nullptr)
        {
            std::cout << "(" + std::to_string(temp->adjacentVertex) + ": " + std::to_string(temp->weight) + "); ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

