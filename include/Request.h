#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

enum RequestState
{
    REQUESTED = 1,
    INDIVIDUAL,
    COMBINED,
    COMPLETED
};

class Request
{
private:
    int id;
    double requestTime;
    double originX, originY;
    double destinationX, destinationY;
    RequestState state;

    double traveledDistance;
    double completionTime;

public:
    Request();
    Request(int id, double time, double ox, double oy, double dx, double dy);

    int getId() const;
    double getRequestTime() const;
    double getOriginX() const;
    double getOriginY() const;
    double getDestinationX() const;
    double getDestinationY() const;
    RequestState getState() const;
    double getTraveledDistance() const;
    double getCompletionTime() const;

    void setState(RequestState newState);
    void setTraveledDistance(double distance);
    void setCompletionTime(double time);

    double calculateODDistance() const;
};

#endif
