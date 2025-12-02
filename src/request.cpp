#include "../include/Request.h"
#include <cmath>

Request::Request()
{
    id = -1;
    requestTime = 0;
    originX = originY = destinationX = destinationY = 0;
    state = REQUESTED;
    traveledDistance = 0;
    completionTime = 0;
}

Request::Request(int id, double time, double ox, double oy, double dx, double dy)
{
    this->id = id;
    this->requestTime = time;
    this->originX = ox;
    this->originY = oy;
    this->destinationX = dx;
    this->destinationY = dy;
    this->state = REQUESTED;
    this->traveledDistance = 0;
    this->completionTime = 0;
}

int Request::getId() const { return id; }
double Request::getRequestTime() const { return requestTime; }
double Request::getOriginX() const { return originX; }
double Request::getOriginY() const { return originY; }
double Request::getDestinationX() const { return destinationX; }
double Request::getDestinationY() const { return destinationY; }
RequestState Request::getState() const { return state; }
double Request::getTraveledDistance() const { return traveledDistance; }
double Request::getCompletionTime() const { return completionTime; }

void Request::setState(RequestState newState) { state = newState; }
void Request::setTraveledDistance(double distance) { traveledDistance = distance; }
void Request::setCompletionTime(double time) { completionTime = time; }

double Request::calculateODDistance() const
{
    double dx = destinationX - originX;
    double dy = destinationY - originY;
    double distance = sqrt(dx * dx + dy * dy);

    return distance;
}
