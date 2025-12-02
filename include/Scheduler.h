#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Ride.h"
#include "Stop.h"

#define EVENT_PICKUP 1
#define EVENT_DROPOFF 2
#define EVENT_COMPLETE 3

struct Event
{
    double time;
    Ride *ride;
    Stop *stop;
    int type;
};

class Scheduler
{
private:
    Event *heap;
    int size;
    int capacity;

    int getParent(int i) const;
    int getLeftChild(int i) const;
    int getRightChild(int i) const;

    void swap(Event &a, Event &b);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Scheduler(int capacity);
    ~Scheduler();

    void insertEvent(double time, Ride *ride, Stop *stop, int type);

    Event extractNextEvent();

    Event peekNextEvent() const;

    bool isEmpty() const;
    void clear();
};

#endif
