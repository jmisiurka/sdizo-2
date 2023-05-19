#ifndef HEAP_H
#define HEAP_H

#include <climits>

//klasa reprezentująca kopiec wykorzystywany jako kolejka priorytetowa
//implementacja tablicowa, minimum w korzeniu
template <class T> class Heap           //w kopcu będą przechowywane różne typy, muszą tylko mieć zaimplementowane
{                                       //operatory porównania (<, >, ==) oraz atrybut id
    int maxSize;
    int currentSize;
    T** table;
public:
    Heap(int size);
    ~Heap();

    void add(T element);

    T& popRoot();

    void fixUp(int index);

    void fixDown(int index);

    int find(int id);

    bool empty();

    T& operator[](int index);
};


//implementacje funkcji
template<class T>
Heap<T>::Heap(int size): currentSize(0)
{
    maxSize = size;
    table = new T*[maxSize];
}

template<class T>
Heap<T>::~Heap()
{
    delete[] table;
}

template<class T>
void Heap<T>::add(T t)
{
    table[currentSize++] = &t;
    fixUp(currentSize - 1);
}

template<class T>
T& Heap<T>::popRoot()
{
    T* root = table[0];

    table[0] = table[currentSize - 1];
    table[currentSize - 1] = nullptr;

    currentSize--;

    fixDown(0);

    return *root;
}

template<class T>
void Heap<T>::fixUp(int index)
{
    if (table[(index - 1) / 2] > table[index])
    {
        T temp = table[(index - 1) / 2];
        table[(index - 1) / 2] = table[index];
        table[index] = temp;
        fixUp((index - 1) / 2);
    }
}

template<class T>
void Heap<T>::fixDown(int index)
{
    T* parent = table[index];
    if (currentSize <= 2 * index + 1)       //brak potomków dla wierzchołka
        return;

    T* childLeft = table[2 * index + 1];

    //jeżeli tylko jeden potomek, to jako drugi podstawiamy też pierwszego, bo przy równości pierwszeństwo ma
    //lewy, a nie musimy przez to rozpatrywać osobno przypadku tylko jednego potomka
    T* childRight = currentSize > (2 * index + 2) ? table[2 * index + 2] : table[2 * index + 1];

    if (parent > childLeft || parent > childRight)
    {
        T* temp = parent;

        if (!(*childLeft > *childRight))
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

template<class T>
int Heap<T>::find(int id)                       //zwraca indeks w tablicy elementu o podanym id
{
    for (int i = 0; i < currentSize; i++)
    {
        if ((*table[i])->id == id)
        {
            return i;
        }
    }

    return -1;
}

template<class T>
bool Heap<T>::empty()
{
    return currentSize == 0;
}

template<class T>
T& Heap<T>::operator[](int index)
{
    return *(table[index]);
}


#endif