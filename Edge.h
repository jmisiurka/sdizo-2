#ifndef EDGE_H
#define EDGE_H

//struktura reprezentująca krawędź grafu przechowywaną w kopcu
struct Edge
{
    int weight;
    int vertexA;
    int vertexB;

    Edge(int weight = 0, int vertexA = -1, int vertexB = -1);

    bool operator<(Edge edge) const;

    bool operator==(Edge edge) const;

    bool operator>(Edge edge) const;
};

#endif
