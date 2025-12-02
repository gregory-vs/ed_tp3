#include "../include/Stop.h"

// Default constructor
Stop::Stop()
{
    x = 0;
    y = 0;
    type = PICKUP;
    passenger = nullptr;
}

// Parameterized constructor
Stop::Stop(double x, double y, StopType type, Request *passenger)
{
    this->x = x;
    this->y = y;
    this->type = type;
    this->passenger = passenger;
}

// Getters
double Stop::getX() const { return x; }
double Stop::getY() const { return y; }
StopType Stop::getType() const { return type; }
Request *Stop::getPassenger() const { return passenger; }
int Stop::getIndexInRide() const { return indexInRide; }

// Setters
void Stop::setX(double x) { this->x = x; }
void Stop::setY(double y) { this->y = y; }
void Stop::setType(StopType type) { this->type = type; }
void Stop::setPassenger(Request *passenger) { this->passenger = passenger; }
void Stop::setIndexInRide(int idx) { indexInRide = idx; }

// Helper
std::string Stop::getTypeDescription() const
{
    return (type == PICKUP) ? "Pickup" : "Dropoff";
}
