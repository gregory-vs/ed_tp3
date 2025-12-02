
#ifndef RIDE_H
#define RIDE_H

#include "../include/Segment.h"
#include "../include/Stop.h"
#include "../include/Request.h"

#define MAXTAM 400

class Ride
{
private:
    int id;

    double duration;
    double totalDistance;
    double efficiency;

    Request *requests[MAXTAM];
    int requestCount;

    Segment *segments[MAXTAM];
    Stop *stops[MAXTAM];

    int segmentCount;
    int stopCount;

public:
    Ride();
    Ride(int id);

    ~Ride();

    void addRequest(Request *request);
    Request *getRequest(int index) const;
    int getRequestCount() const;

    void addSegment(Segment *segment);
    void addStop(Stop *stop);
    Stop *getStop(int i) const;
    int getStopCount() const;
    void addDistance(double d);
    Segment *getSegment(int index) const;

    int getId() const;
    double getDuration() const;
    double getTotalDistance() const;
    double getEfficiency() const;
    Request *getFirstRequest();

    void setDuration(double duration);
    void setTotalDistance(double distance);
    void setEfficiency(double efficiency);
};

#endif
