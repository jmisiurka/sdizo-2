#ifndef HEAP_H
#define HEAP_H

#include "Edge.h"

//klasa reprezentująca kopiec wykorzystywany jako kolejka priorytetowa
//w algorytmach wymagających sortowania wag krawędzi
//implementacja tablicowa, minimum w korzeniu
class Heap
{
    int currentSize;
    Edge* table;
public:
    Heap(int size);
    ~Heap();

    void add(Edge edge);

    Edge popRoot();

    void fixUp(int index);

    void fixDown(int index);

    Edge& operator[](int index);
};

#endif