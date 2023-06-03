#include "Queue.h"

QueueNode::QueueNode(int data)
{
    this->data = data;
    next = nullptr;
}

Queue::Queue()
{
    front = nullptr;
    end = nullptr;
}

Queue::~Queue()
{
    while (front != nullptr)
    {
        dequeue();
    }
}

void Queue::enqueue(int data)
{
    QueueNode* node = new QueueNode(data);

    if (front == nullptr)
    {
        front = node;
    } else
    {
        end->next = node;
    }

    end = node;
}

int Queue::dequeue()
{
    if (front == nullptr)
    {
        return -1;
    }

    int data = front->data;

    QueueNode* temp = front;

    if (front == end)
    {
        front = nullptr;
        end = nullptr;
    } else
    {
        front = front->next;
    }

    delete temp;

    return data;
}

bool Queue::empty()
{
    return front == nullptr;
}