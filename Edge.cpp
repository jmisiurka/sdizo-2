#include "Heap.h"
#include "Edge.h"


Edge::Edge(int weight, int vertexA, int vertexB)
{
    this->weight = weight;
    this->vertexA = vertexA;
    this->vertexB = vertexB;
}

bool Edge::operator<(Edge edge) const
{
    return this->weight < edge.weight;
}

bool Edge::operator==(Edge edge) const
{
    return this->weight == edge.weight;
}

bool Edge::operator>(Edge edge) const
{
    return this->weight > edge.weight;
}