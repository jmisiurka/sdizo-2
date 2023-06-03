#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode
{
    int data;
    QueueNode* next;

    QueueNode(int data);
};

class Queue
{
    QueueNode* front;
    QueueNode* end;

public:
    Queue();
    ~Queue();

    void enqueue(int data);

    int dequeue();

    bool empty();
};

#endif