#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "Heap.h"

int main()
{
    AdjacencyMatrix matrix = AdjacencyMatrix(0);

    matrix.loadFromFile("mst.txt");

    matrix.print();
}
