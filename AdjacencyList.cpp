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

void AdjacencyList::loadFromFile(const std::string &filename, int problem, int* additionalValues)
{
    std::ifstream filestream(filename);

    if (!filestream.is_open())
    {
        std::cout << "Błąd podczas otwierania pliku" << std::endl;
        return;
    }

    if (list != nullptr)
    {
        clearList();
    }

    int numberOfEdges, numberOfVertices;
    filestream >> numberOfEdges;
    filestream >> numberOfVertices;

    if (problem == 1)
    {
        filestream >> *additionalValues;            //wczytanie wierzchołka początkowego dla shortpath
    } else if (problem == 2)
    {
        filestream >> additionalValues[0];          //wczytanie wierzchołków dla problemu przepływu
        filestream >> additionalValues[1];
    }

    V = numberOfVertices;

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

        if (problem == 0)                //jeśli graf nie jest skierowany, to wrzucamy krawędź do obu wierzchołków
        {
            if (list[vertexB] == nullptr)                   //lista krawędzi przy B jest pusta
            {
                list[vertexB] = new AdjacencyListNode();
                list[vertexB]->next = nullptr;
                list[vertexB]->adjacentVertex = vertexA;
                list[vertexB]->weight = weight;
            } else
            {                                            //lista krawędzi przy B nie jest pusta
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

int AdjacencyList::countTotalWeight()
{
    int sum = 0;
    for (int i = 0; i < V; i++)
    {
        AdjacencyListNode* temp = list[i];
        while (temp != nullptr)
        {
            sum += temp->weight;
            temp = temp->next;
        }
    }
    return sum;                             //jeżeli graf jest nieskierowany, to trzeba pamiętać, że wynik jest podwojony
}

void AdjacencyList::MST_Prim(int starting)
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
    Q.heapify();                             //naprawa całego kopca

    while (!Q.empty())
    {
        u = Q.popRoot()->id;                //pobranie elementu z kolejki

        AdjacencyListNode* node = list[u];
        while (node != nullptr)
        {
            if (!considered[node->adjacentVertex] && vertices[node->adjacentVertex].key > node->weight)
            {
                vertices[node->adjacentVertex].key = node->weight;
                vertices[node->adjacentVertex].previous = u;
                Q.heapify();
            }
            node = node->next;
        }
        considered[u] = true;
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

    mst.print();
    std::cout << "Całkowita waga krawędzi: " << mst.countTotalWeight() / 2 << std::endl;
}

void AdjacencyList::MST_Kruskal()
{
    Edge mstEdges[V - 1];                           //V - 1 krawędzi w MST
    Edge allEdges[V * (V - 1) / 2];                 //max krawędzi w grafie: V * (V - 1) / 2
    Heap Q = Heap<Edge *>(
            V * (V - 1) / 2);      //kopiec operuje na wskaźnikach, więc tablica wyżej jest trochę sztuczna

    int edgeCount = 0;

    for (int i = 0; i < V; i++)                     //kolejka krawędzi posortowana rosnąco
    {
        AdjacencyListNode *temp = list[i];
        while (temp != nullptr)
        {
            if (temp->adjacentVertex >= i)
            {
                Edge edge = Edge();
                edge.weight = temp->weight;
                edge.vertexA = i;
                edge.vertexB = temp->adjacentVertex;
                allEdges[edgeCount] = edge;
                Q.add(&(allEdges[edgeCount]));
                edgeCount++;
            }
            temp = temp->next;
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

int AdjacencyList::Kruskal_parent(int vertex, int *parents)
{
    if (parents[vertex] != vertex)
    {
        parents[vertex] = Kruskal_parent(parents[vertex], parents);
    }
    return parents[vertex];
}

void AdjacencyList::Shortpath_Dijkstra(int starting)
{
    DistPrevPair vertices[V];
    bool considered[V];

    Heap Q = Heap<DistPrevPair *>(V);
    //to może mieć wpływ na złożoność
    for (int i = 0; i < V; i++)             //przypisanie numerów wierzchołków (póki co wszystkie elementy takie same)
    {
        vertices[i].id = i;
        Q.add(&vertices[i]);
        considered[i] = false;
    }

    int u = starting;

    vertices[u].distance = 0;
    Q.heapify();

    while (!Q.empty())
    {
        u = Q.popRoot()->id;

        AdjacencyListNode* node = list[u];
        while (node != nullptr)
        {
            if (!considered[node->adjacentVertex] && vertices[node->adjacentVertex].distance > node->weight + vertices[u].distance)
            {
                vertices[node->adjacentVertex].distance = node->weight + vertices[u].distance;
                vertices[node->adjacentVertex].previous = u;
                Q.heapify();
            }
            node = node->next;
        }
        considered[u] = true;
    }

    std::cout << "Dijkstra - lista sąsiedztwa" << std::endl;

    for (int i = 0; i < V; i++)
    {
        std::cout << "Wierzchołek: " << i << std::endl;
        std::cout << "\tOdległość od wierzchołka początkowego: " << vertices[i].distance << std::endl;
        std::cout << "\tDroga: " << i;
        int temp = vertices[i].previous;
        while (temp >= 0)
        {
            std::cout << "<-" << temp;
            temp = vertices[temp].previous;
        }
        std::cout << std::endl;
    }
}

void AdjacencyList::Shortpath_BF(int starting)
{
    DistPrevPair vertices[V];
    bool considered[V];

    for (int i = 0; i < V; i++)                     //kolejka krawędzi posortowana rosnąco
    {
        vertices[i].id = i;
        considered[i] = false;
    }

    int u = starting;
    vertices[u].distance = 0;

    bool changed = true;                            //jeżeli w przejściu nic się nie zmieni, to można skończyć
    for (int i = 0; i < V && changed; i++)
    {
        changed = false;

        for (int j = 0; j < V; j++)
        {
            AdjacencyListNode *temp = list[j];
            while (temp != nullptr)
            {
                if (vertices[temp->adjacentVertex].distance > vertices[j].distance + temp->weight)
                {
                    changed = true;

                    vertices[temp->adjacentVertex].distance = vertices[j].distance + temp->weight;
                    vertices[temp->adjacentVertex].previous = j;
                }

                temp = temp->next;
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        AdjacencyListNode *temp = list[i];
        while (temp != nullptr)
        {
            if (vertices[temp->adjacentVertex].distance > vertices[i].distance + temp->weight)
            {
                std::cout << "W grafie wystąpił cykl o wadze ujemnej - wyniki są nieprawidłowe" << std::endl;
                return;
            }

            temp = temp->next;
        }
    }

    std::cout << "Bellman-Ford - lista sąsiedztwa" << std::endl;

    for (int i = 0; i < V; i++)
    {
        std::cout << "Wierzchołek: " << i << std::endl;
        std::cout << "\tOdległość od wierzchołka początkowego: " << vertices[i].distance << std::endl;
        std::cout << "\tDroga: " << i;
        int temp = vertices[i].previous;
        while (temp >= 0)
        {
            std::cout << "<-" << temp;
            temp = vertices[temp].previous;
        }
        std::cout << std::endl;
    }
}