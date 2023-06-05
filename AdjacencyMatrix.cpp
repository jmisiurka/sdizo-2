#include <climits>
#include <random>
#include <chrono>
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

void AdjacencyMatrix::loadFromFile(const std::string &filename, int problem, int *additionalValues)
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

    if (problem == 1)
    {
        filestream >> *additionalValues;            //wczytanie wierzchołka początkowego dla shortpath
    } else if (problem == 2)
    {
        filestream >> additionalValues[0];          //wczytanie wierzchołków dla problemu przepływu
        filestream >> additionalValues[1];
    }

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
        if (problem == 0)
        {
            matrix[vertexB][vertexA] = weight;
        }
    }

    filestream.close();
}

void AdjacencyMatrix::generateRandomGraph(int graphV, bool directed, int minWeight, int maxWeight, int densityLevel)
{
    for (int i = 0; i < V; i++)                     //usunięcie dotychczasowej macierzy
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    V = graphV;
    matrix = new int *[V];                           //alokacja 1 wymiaru tablicy
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];                     //alokacja 2 wymiaru tablicy i wyzerowanie wszystkich komórek
        for (int j = 0; j < V; j++)
        {
            matrix[i][j] = 0;
        }
    }

    std::default_random_engine rng(
            std::chrono::system_clock::now().time_since_epoch().count());    //generator liczb pseudolosowych
    std::uniform_int_distribution<int> random_int;

    if (!directed)
    {
        int maxEdges = V * (V - 1) / 2;
        if (densityLevel == 3)      //99%
        {
            for (int i = 0; i < V; i++)     //wygenerowanie wszystkich możliwych krawędzi
            {
                for (int j = i + 1; j < V; j++)
                {
                    int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                    matrix[i][j] = weight;
                    matrix[j][i] = weight;
                }
            }

            int nOfEdges = 0.99f * maxEdges;
            int removeCounter = maxEdges - nOfEdges;
            while (removeCounter > 0)       //usunięcie 1% krawędzi
            {
                int vertexA = random_int(rng) % V;
                int vertexB = random_int(rng) % V;
                if (matrix[vertexA][vertexB] != 0)
                {
                    matrix[vertexA][vertexB] = 0;
                    matrix[vertexB][vertexA] = 0;
                    removeCounter--;
                }
            }
        } else
        {                    //20% lub 60%
            int nOfEdges;
            if (densityLevel == 1)
            {
                nOfEdges = 0.2f * maxEdges;
            } else
            {
                nOfEdges = 0.6f * maxEdges;
            }

            int edgeCount = 0;

            for (int i = 1; i < V; i++)         //prosty sposób generowania drzewa rozpinającego
            {
                bool created = false;
                int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;

                while (!created)
                {
                    int adjacentVertex = random_int(rng) % i;
                    if (matrix[i][adjacentVertex] == 0)
                    {
                        matrix[i][adjacentVertex] = weight;
                        matrix[adjacentVertex][i] = weight;
                        created = true;
                        edgeCount++;
                    }
                }
            }

            while (edgeCount < nOfEdges)            //generowanie nowych krawędzi do określonej gęstości
            {
                int vertexA = random_int(rng) % V;
                int vertexB = random_int(rng) % V;
                int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                if (vertexA != vertexB && matrix[vertexA][vertexB] == 0)
                {
                    matrix[vertexA][vertexB] = weight;
                    matrix[vertexB][vertexA] = weight;
                    edgeCount++;
                }
            }
        }
    } else
    {                //graf skierowany
        int maxEdges = V * (V - 1);
        if (densityLevel == 3)      //99%
        {
            for (int i = 0; i < V; i++)     //wygenerowanie wszystkich możliwych krawędzi
            {
                for (int j = 0; j < V; j++)
                {
                    int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                    matrix[i][j] = weight;
                    weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                    matrix[j][i] = weight;
                }
            }

            int nOfEdges = 0.99f * maxEdges;
            int removeCounter = maxEdges - nOfEdges;
            while (removeCounter > 0)       //usunięcie 1% krawędzi
            {
                int vertexA = random_int(rng) % V;
                int vertexB = random_int(rng) % V;
                if (matrix[vertexA][vertexB] != 0)
                {
                    matrix[vertexA][vertexB] = 0;
                    matrix[vertexB][vertexA] = 0;
                    removeCounter--;
                }
            }
        } else
        {                    //20% lub 60%
            int nOfEdges;
            if (densityLevel == 1)
            {
                nOfEdges = 0.2f * maxEdges;
            } else
            {
                nOfEdges = 0.6f * maxEdges;
            }

            int edgeCount = 0;

            for (int i = 1; i < V; i++)         //prosty sposób generowania drzewa rozpinającego
            {
                bool created = false;
                int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;

                while (!created)
                {
                    int adjacentVertex = random_int(rng) % i;
                    if (matrix[i][adjacentVertex] == 0)
                    {
                        matrix[i][adjacentVertex] = weight;
                        created = true;
                        edgeCount++;
                    }
                }
            }


            while (edgeCount < nOfEdges)            //generowanie nowych krawędzi do określonej gęstości
            {
                int vertexA = random_int(rng) % V;
                int vertexB = random_int(rng) % V;
                int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                if (vertexA != vertexB && matrix[vertexA][vertexB] == 0)
                {
                    matrix[vertexA][vertexB] = weight;
                    edgeCount++;
                }
            }

            for (int i = 0; i < V; i++)    //weryfikacja czy do każdego wierzchołka można dotrzeć
            {
                bool canBeReached = false;
                for (int j = 0; j < V; j++)
                {
                    if (matrix[j][i] != 0)
                    {
                        canBeReached = true;
                        break;
                    }
                }

                if (!canBeReached)
                {
                    bool created = false;
                    while (!created)
                    {
                        int vertex = random_int(rng) % V;
                        int weight = (random_int(rng) % (maxWeight + 1 - minWeight)) + minWeight;
                        if (vertex != i)
                        {
                            matrix[vertex][i] = weight;     //utworzenie krawędzi do wierzchołka
                            created = true;
                        }
                    }
                }
            }
        }
    }
}

int AdjacencyMatrix::get(int vertexA, int vertexB) const
{
    return matrix[vertexA][vertexB];
}

int AdjacencyMatrix::getV() const
{
    return V;
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

void AdjacencyMatrix::MST_Prim(int starting, bool test)
{
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

    if (!test)
    {
        int sum = 0;

        for (KeyPrevPair pair: vertices)
        {
            int vertexA = pair.id;
            int vertexB = pair.previous;


            if (vertexB != -1)
            {
                sum += matrix[vertexA][vertexB];
                std::cout << "(" << vertexA << " - " << vertexB << ", " << matrix[vertexA][vertexB] << ")" << std::endl;
            }
        }

        std::cout << "Suma wag krawędzi:" << sum << std::endl << std::endl;
    }
}

void AdjacencyMatrix::MST_Kruskal(bool test)
{
    Edge mstEdges[V - 1];                           //V - 1 krawędzi w MST
    Edge allEdges[V * (V - 1) / 2];                 //max krawędzi w grafie: V * (V - 1) / 2
    int rank[V];
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
        rank[i] = 0;
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
            if (rank[parent[edge.vertexA]] > rank[parent[edge.vertexB]])
            {
                parent[parent[edge.vertexB]] = parentA;
            } else {
                parent[parent[edge.vertexA]] = parentB;
                if (rank[parent[edge.vertexA]] == rank[parent[edge.vertexB]])
                {
                    rank[parent[edge.vertexB]]++;
                }
            }
        }
    }

    if (!test)
    {
        int sum = 0;
        for (Edge edge: mstEdges)
        {
            sum += edge.weight;
            std::cout << "(" << edge.vertexA << " - " << edge.vertexB << ", " << edge.weight << ")" << std::endl;
        }
        std::cout << "Suma wag krawędzi: " << sum << std::endl;
    }
}

int AdjacencyMatrix::Kruskal_parent(int vertex, int *parents)
{
    if (parents[vertex] != vertex)
    {
        parents[vertex] = Kruskal_parent(parents[vertex], parents);
    }
    return parents[vertex];
}

void AdjacencyMatrix::shortpath_Dijkstra(int starting, bool test)
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
        for (int i = 0; i < V; i++)
        {
            if (!considered[i] && matrix[u][i] != 0)
            {
                if (matrix[u][i] + vertices[u].distance <
                    vertices[i].distance)     //ścieżka przez u krótsza niż dotychczasowa
                {
                    vertices[i].distance = matrix[u][i] + vertices[u].distance;
                    vertices[i].previous = u;
                    Q.heapify();
                }
            }
        }
        considered[u] = true;
    }


    if (!test)
    {
        std::cout << "Dijkstra - macierz sąsiedztwa" << std::endl;

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
}

void AdjacencyMatrix::shortpath_BF(int starting, bool test)
{
    DistPrevPair vertices[V];

    for (int i = 0; i < V; i++)                     //kolejka krawędzi posortowana rosnąco
    {
        vertices[i].id = i;
    }

    int u = starting;
    vertices[u].distance = 0;

    bool changed = true;                            //jeżeli w przejściu nic się nie zmieni, to można skończyć
    for (int i = 0; i < V && changed; i++)
    {
        changed = false;
        for (int a = 0; a < V; a++)
        {
            for (int b = 0; b < V; b++)
            {
                if (vertices[a].distance == INT_MAX)
                    break;

                if (matrix[a][b] != 0 && vertices[b].distance > vertices[a].distance + matrix[a][b])
                {
                    changed = true;

                    vertices[b].distance = vertices[a].distance + matrix[a][b];
                    vertices[b].previous = a;
                }
            }
        }
    }

    for (int i = 0; i < V; i++)                            //sprawdzenie cykli ujemnych
    {
        for (int j = 0; j < V; j++)
        {
            if (matrix[i][j] != 0 && vertices[j].distance > vertices[i].distance + matrix[i][j])
            {
                std::cout << "W grafie wystąpił cykl o wadze ujemnej - wyniki są nieprawidłowe" << std::endl;
                return;
            }
        }
    }

    if (!test)
    {
        std::cout << "Bellman-Ford - macierz sąsiedztwa" << std::endl;

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
}

bool AdjacencyMatrix::BFS(int start, int end, int *parents)
{
    char color[V];
    for (int i = 0; i < V; i++)
    {
        parents[i] = -1;
        color[i] = 'W';
    }

    color[start] = 'G';
    parents[start] = start;
    Queue q;
    q.enqueue(start);

    int u;

    while (!q.empty())
    {
        u = q.dequeue();
        for (int i = 0; i < V; i++)
        {
            if (matrix[u][i] > 0 && color[i] == 'W')
            {
                parents[i] = u;
                if (i == end)
                {
                    return true;        //znaleziono drogę ze start do end, koniec
                }
                color[i] = 'G';
                q.enqueue(i);
            }
        }
        color[u] = 'B';
    }

    return false;               //nie znaleziono drogi z start do end
}

bool AdjacencyMatrix::DFS(int start, int end, int *parents)
{
    char color[V];
    for (int i = 0; i < V; i++)
    {
        color[i] = 'W';
        parents[i] = -1;
    }

    color[start] = 'G';

    return DFSVisit(start, end, color, parents);
}

bool AdjacencyMatrix::DFSVisit(int u, int end, char *color, int *parents)
{
    color[u] = 'G';
    bool foundEnd = false;

    for (int v = 0; v < V; v++)
    {
        if (foundEnd)
        {
            break;
        }

        if (matrix[u][v] > 0 && color[v] == 'W')
        {
            parents[v] = u;
            if (v == end)
            {
                return true;
            }
            foundEnd = DFSVisit(v, end, color, parents);
        }
    }

    return foundEnd;
}

void AdjacencyMatrix::Ford_Fulkerson(int start, int end, int pathfinding, bool test)
{
    AdjacencyMatrix residualGraph = AdjacencyMatrix(V);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            residualGraph.matrix[i][j] = matrix[i][j];
        }
    }

    int parent[V];

    int maxFlow = 0;

    bool pathExists;
    if (pathfinding == 1)
    {
        pathExists = residualGraph.BFS(start, end, parent);
    } else if (pathfinding == 2)
    {
        pathExists = residualGraph.DFS(start, end, parent);
    }

    std::string outputText("Algorytm Forda-Fulkersona: macierz sąsiedztwa\n"
                               "Ścieżki przepływu:\n");

    do
    {
        int pathFlow = INT_MAX;

        for (int i = end; i != start; i = parent[i])        //przejście od końca do początku po ścieżce
        {
            outputText.append(std::to_string(i) + "<-");
            int j = parent[i];
            if (pathFlow > residualGraph.matrix[j][i])              //szukamy połączenia o najmniejszym przepływie
            {
                pathFlow = residualGraph.matrix[j][i];
            }
        }
        outputText.append(std::to_string(start) + ", przepływ: " + std::to_string(pathFlow) + "\n");

        for (int i = end; i != start; i = parent[i])            //zmieniamy przepływ w grafie rezydualnym
        {
            int j = parent[i];
            residualGraph.matrix[j][i] -= pathFlow;
            residualGraph.matrix[i][j] += pathFlow;
        }

        maxFlow += pathFlow;

        if (pathfinding == 1)
        {
            pathExists = residualGraph.BFS(start, end, parent);
        } else if (pathfinding == 2)
        {
            pathExists = residualGraph.DFS(start, end, parent);
        }
    } while (pathExists);

    if (!test)
    {
        std::cout << outputText;

        std::cout << "Maksymalny przepływ: " << maxFlow << std::endl;
    }
}