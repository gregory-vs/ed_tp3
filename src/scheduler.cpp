#include "../include/Scheduler.h"
#include <iostream>

int Scheduler::getParent(int i) const { return (i - 1) / 2; }
int Scheduler::getLeftChild(int i) const { return (2 * i) + 1; }
int Scheduler::getRightChild(int i) const { return (2 * i) + 2; }

void Scheduler::swap(Event &a, Event &b)
{
    Event temp = a;
    a = b;
    b = temp;
}

void Scheduler::heapifyUp(int index)
{
    while (index > 0 && heap[getParent(index)].time > heap[index].time)
    {
        swap(heap[getParent(index)], heap[index]);
        index = getParent(index);
    }
}

void Scheduler::heapifyDown(int index)
{
    int smallest = index;
    int left = getLeftChild(index);
    int right = getRightChild(index);

    if (left < size && heap[left].time < heap[smallest].time)
        smallest = left;

    if (right < size && heap[right].time < heap[smallest].time)
        smallest = right;

    if (smallest != index)
    {
        swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

Scheduler::Scheduler(int capacity)
{
    this->capacity = capacity;
    heap = new Event[capacity];
    size = 0;
}

Scheduler::~Scheduler()
{
    delete[] heap;
}

void Scheduler::insertEvent(double time, Ride *ride, Stop *stop, int type)
{
    if (size >= capacity)
    {
        std::cerr << "Scheduler overflow: cannot insert more events.\n";
        return;
    }

    Event newEvent;
    newEvent.time = time;
    newEvent.ride = ride;
    newEvent.stop = stop;
    newEvent.type = type;

    heap[size] = newEvent;
    heapifyUp(size);
    size++;
}

Event Scheduler::extractNextEvent()
{
    if (size == 0)
    {
        Event empty = {0, nullptr, nullptr, -1};
        return empty;
    }

    Event root = heap[0];
    heap[0] = heap[size - 1];
    size--;

    heapifyDown(0);

    return root;
}

Event Scheduler::peekNextEvent() const
{
    if (size == 0)
    {
        Event empty = {0, nullptr, nullptr, -1};
        return empty;
    }
    return heap[0];
}

bool Scheduler::isEmpty() const
{
    return size == 0;
}

void Scheduler::clear()
{
    size = 0;
}
