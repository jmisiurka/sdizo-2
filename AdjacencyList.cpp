#include "AdjacencyList.h"
#include "Heap.h"

AdjacencyList::AdjacencyList(int V) : V(V)
{
    if (V == 0)
    {
        list = nullptr;
        return;
    }
    list = new AdjacencyListNode* [V];                   //alokacja pamięci pod listy
    for (int i = 0; i < V; i++)
    {
        list[i] = nullptr;
    }
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

void AdjacencyList::loadFromFile(const std::string &filename)
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

    V = numberOfVertices;

    if (list != nullptr)
    {
        clearList();
    }

    delete[] list;
    list = new AdjacencyListNode* [V];
    for (int i = 0; i < V; i++)
    {
        list[i] = nullptr;
    }

    for (int i = 0; i < numberOfEdges; i++)
    {
        int vertexA, vertexB, weight;
        filestream >> vertexA;
        filestream >> vertexB;
        filestream >> weight;

        if (list[vertexA] == nullptr)                   //lista krawędzi przy A jest pusta
        {
            list[vertexA] = new AdjacencyListNode();
            list[vertexA]->next = nullptr;
            list[vertexA]->adjacentVertex = vertexB;
            list[vertexA]->weight = weight;
        } else
        {                                            //lista krawędzi przy A nie jest pusta
            AdjacencyListNode *temp = list[vertexA];
            while (temp->next != nullptr)                   //przejście do ostatniego elementu listy
            {
                temp = temp->next;
            }

            temp->next = new AdjacencyListNode();           //utworzenie nowego elementu
            temp = temp->next;
            temp->next = nullptr;
            temp->adjacentVertex = vertexB;
            temp->weight = weight;
        }

        if (list[vertexB] == nullptr)                   //lista krawędzi przy A jest pusta
        {
            list[vertexB] = new AdjacencyListNode();
            list[vertexB]->next = nullptr;
            list[vertexB]->adjacentVertex = vertexA;
            list[vertexB]->weight = weight;
        } else
        {                                            //lista krawędzi przy A nie jest pusta
            AdjacencyListNode *temp = list[vertexB];
            while (temp->next != nullptr)                   //przejście do ostatniego elementu listy
            {
                temp = temp->next;
            }

            temp->next = new AdjacencyListNode();           //utworzenie nowego elementu
            temp = temp->next;
            temp->next = nullptr;
            temp->adjacentVertex = vertexA;
            temp->weight = weight;
        }
    }

    filestream.close();
}

int AdjacencyList::get(int vertexA, int vertexB) const
{
    AdjacencyListNode *temp = list[vertexA];
    while (temp != nullptr)
    {
        if (temp->adjacentVertex == vertexB)            //krawędź łącząca A i B
        {
            return temp->weight;
        }
        temp = temp->next;
    }

    return 0;                                           //brak krawędzi łączącej A i B
}

void AdjacencyList::clearList()                         //czyszczenie zawartości listy
{
    for (int i = 0; i < V; i++)
    {
        AdjacencyListNode* head = list[i];
        if (head != nullptr)
        {
            while (head->next != nullptr)
            {
                AdjacencyListNode *temp = head;
                head = head->next;
                delete temp;
            }
            delete head;

            list[i] = nullptr;
        }
    }
}

void AdjacencyList::print() const
{
    for (int i = 0; i < V; i++)
    {
        AdjacencyListNode* temp = list[i];
        std::cout << i << ": ";
        while (temp != nullptr)
        {
            std::cout << "(" + std::to_string(temp->adjacentVertex) + ", " + std::to_string(temp->weight) + "); ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

AdjacencyList AdjacencyList::MST_Prim(int starting)
{
    AdjacencyList mst = AdjacencyList(V);

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

        AdjacencyListNode* node = list[u];
        while (node != nullptr)
        {
            if (!considered[node->adjacentVertex] && vertices[node->adjacentVertex].key > vertices[u].key + node->weight)
            {
                vertices[node->adjacentVertex].key = vertices[u].key + node->weight;
                vertices[node->adjacentVertex].previous = u;
            }
            node = node->next;
        }
    }

    for (KeyPrevPair pair : vertices)
    {
        int vertexA = pair.id;
        int vertexB = pair.previous;

        if (vertexB >= 0)                                      //pomijamy dla wierzchołka startowego
        {
            if (mst.list[vertexA] == nullptr)                   //lista krawędzi przy A jest pusta
            {
                mst.list[vertexA] = new AdjacencyListNode();
                mst.list[vertexA]->next = nullptr;
                mst.list[vertexA]->adjacentVertex = vertexB;
                mst.list[vertexA]->weight = get(vertexA, vertexB);
            } else
            {                                            //lista krawędzi przy A nie jest pusta
                AdjacencyListNode *temp = mst.list[vertexA];
                while (temp->next != nullptr)                   //przejście do ostatniego elementu listy
                {
                    temp = temp->next;
                }

                temp->next = new AdjacencyListNode();           //utworzenie nowego elementu
                temp = temp->next;
                temp->next = nullptr;
                temp->adjacentVertex = vertexB;
                temp->weight = get(vertexA, vertexB);
            }

            if (mst.list[vertexB] == nullptr)                   //lista krawędzi przy A jest pusta
            {
                mst.list[vertexB] = new AdjacencyListNode();
                mst.list[vertexB]->next = nullptr;
                mst.list[vertexB]->adjacentVertex = vertexA;
                mst.list[vertexB]->weight = get(vertexA, vertexB);
            } else
            {                                            //lista krawędzi przy A nie jest pusta
                AdjacencyListNode *temp = mst.list[vertexB];
                while (temp->next != nullptr)                   //przejście do ostatniego elementu listy
                {
                    temp = temp->next;
                }

                temp->next = new AdjacencyListNode();           //utworzenie nowego elementu
                temp = temp->next;
                temp->next = nullptr;
                temp->adjacentVertex = vertexA;
                temp->weight = get(vertexA, vertexB);
            }
        }
    }

    return mst;
}

