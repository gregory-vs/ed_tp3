#ifndef STOP_H
#define STOP_H

#include "Request.h"

enum StopType
{
    PICKUP,
    DROPOFF
};

class Stop
{
private:
    double x;
    double y;
    StopType type;
    Request *passenger;
    int indexInRide;

public:
    Stop();
    Stop(double x, double y, StopType type, Request *passenger);

    double getX() const;
    double getY() const;
    StopType getType() const;
    Request *getPassenger() const;
    int getIndexInRide() const;

    void setX(double x);
    void setY(double y);
    void setType(StopType type);
    void setPassenger(Request *passenger);
    void setIndexInRide(int idx);

    std::string getTypeDescription() const;
};

#endif
