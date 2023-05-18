#include <climits>
#include "Heap.h"

template<class T>
Heap<T>::Heap(int size): currentSize(0)
{
    table = new T[size];
}

template<class T>
Heap<T>::~Heap()
{
    delete[] table;
}

template<class T>
void Heap<T>::add(T t)
{
    table[currentSize++] = t;
    fixUp(currentSize - 1);
}

template<class T>
T Heap<T>::popRoot()
{
    T root = table[0];

    table[0] = table[currentSize - 1];
    table[currentSize - 1] = T();

    fixDown(0);

    currentSize--;
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
    T parent = table[index];
    if (currentSize <= 2 * index + 1)       //brak potomków dla wierzchołka
        return;

    T childLeft = table[2 * index + 1];

    //jeżeli tylko jeden potomek, to jako drugi podstawiamy minimalną wartość do porównania, żeby na pewno nie zamienić
    //jeżeli jest tylko 1 potomek, to jako prawego wstawiamy sztuczną krawędź o wadze, która w porównaniu zawsze da
    //ten sam wynik (previous < childRight == true)
    T childRight = currentSize > (2 * index + 2) ? table[2 * index + 2] : T(INT_MAX, -1, -1);

    if (parent > childLeft || parent > childRight)
    {
        T temp = parent;

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

template<class T>
T &Heap<T>::operator[](int index)
{
    return table[index];
}

