#ifndef HEAP_H
#define HEAP_H

//klasa reprezentująca kopiec wykorzystywany jako kolejka priorytetowa
//implementacja tablicowa, minimum w korzeniu
template <class T> class Heap           //w kopcu będą przechowywane różne typy, muszą tylko mieć zaimplementowane
{                                       //operatory porównania (<, >, ==)
    int currentSize;
    T* table;
public:
    Heap(int size);
    ~Heap();

    void add(T element);

    T popRoot();

    void fixUp(int index);

    void fixDown(int index);

    T& operator[](int index);
};

#endif