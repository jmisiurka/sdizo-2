#include <climits>
#include "Heap.h"

Heap::Heap(int size): currentSize(0)
{
    table = new Edge[size];
}

Heap::~Heap()
{
    delete[] table;
}

void Heap::add(Edge edge)
{
    table[currentSize++] = edge;
    fixUp(currentSize - 1);
}

Edge Heap::popRoot()
{
    Edge root = table[0];

    table[0] = table[currentSize - 1];
    table[currentSize - 1] = Edge(0, -1, -1);

    fixDown(0);

    currentSize--;
}

void Heap::fixUp(int index)
{
    if (table[(index - 1) / 2] > table[index])
    {
        Edge temp = table[(index - 1) / 2];
        table[(index - 1) / 2] = table[index];
        table[index] = temp;
        fixUp((index - 1) / 2);
    }
}

void Heap::fixDown(int index)
{
    Edge parent = table[index];
    if (currentSize <= 2 * index + 1)       //brak potomków dla wierzchołka
        return;

    Edge childLeft = table[2 * index + 1];

    //jeżeli tylko jeden potomek, to jako drugi podstawiamy minimalną wartość do porównania, żeby na pewno nie zamienić
    //jeżeli jest tylko 1 potomek, to jako prawego wstawiamy sztuczną krawędź o wadze, która w porównaniu zawsze da
    //ten sam wynik (parent < childRight == true)
    Edge childRight = currentSize > (2 * index + 2) ? table[2 * index + 2] : Edge(INT_MAX, -1, -1);

    if (parent > childLeft || parent > childRight)
    {
        Edge temp = parent;

        if (!(childLeft > childRight))
        {
            table[index] = childLeft;
            table[2 * index + 1] = temp;
            fixDown(2 * index + 1);
        } else
        {
            table[index] = childRight;
            table[2 * index + 2] = temp;
            fixDown(2 * index + 2);
        }
    }
}

Edge &Heap::operator[](int index)
{
    return table[index];
}

