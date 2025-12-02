#include "../include/Ride.h"
#include <iostream>
#include <cmath>

Ride::Ride()
{
    id = -1;
    requestCount = 0;
    duration = 0;
    totalDistance = 0;
    efficiency = 0;
    segmentCount = 0;
    stopCount = 0;
}

Ride::Ride(int id)
{
    this->id = id;
    requestCount = 0;
    duration = 0;
    totalDistance = 0;
    efficiency = 0;
    segmentCount = 0;
    stopCount = 0;
}

Ride::~Ride()
{
}

void Ride::addRequest(Request *request)
{
    if (requestCount < MAXTAM)
    {
        requests[requestCount++] = request;
    }
    else
    {
        std::cerr << "Error: ride " << id << " reached max request capacity." << std::endl;
    }
}

Request *Ride::getRequest(int index) const
{
    if (index >= 0 && index < requestCount)
        return requests[index];
    return nullptr;
}

int Ride::getRequestCount() const { return requestCount; }

void Ride::addSegment(Segment *segment)
{
    segments[segmentCount++] = segment;
}

Segment *Ride::getSegment(int index) const
{
    if (index < 0 || index >= segmentCount)
        return nullptr;

    return segments[index];
}

void Ride::addStop(Stop *stop)
{
    stop->setIndexInRide(stopCount);
    stops[stopCount++] = stop;
}

Stop *Ride::getStop(int i) const
{
    return stops[i];
}

int Ride::getStopCount() const
{
    return stopCount;
}

void Ride::addDistance(double d) {
    totalDistance += d;
}

Request *Ride::getFirstRequest(){
    return this->requests[0];
}

int Ride::getId() const { return id; }
double Ride::getDuration() const { return duration; }
double Ride::getTotalDistance() const { return totalDistance; }
double Ride::getEfficiency() const { return efficiency; }

void Ride::setDuration(double duration) { this->duration = duration; }
void Ride::setTotalDistance(double distance) { this->totalDistance = distance; }
void Ride::setEfficiency(double efficiency) { this->efficiency = efficiency; }
