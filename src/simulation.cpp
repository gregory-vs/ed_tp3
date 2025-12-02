#include "../include/Simulation.h"
#include "../include/Request.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

#define MAX_REQUESTS 2000
#define MAX_RIDES 1000
#define MAX_EVENTS 5000

Simulation::Simulation()
{
    scheduler = new Scheduler(MAX_EVENTS);
    requests = new Request *[MAX_REQUESTS];
    requestCount = 0;
    rides = new Ride *[MAX_RIDES];
    rideCount = 0;
    currentTime = 0;
    totalDistance = 0;
    totalEfficiency = 0;
    completedRides = 0;
}

Simulation::~Simulation()
{
    delete scheduler;
    for (int i = 0; i < requestCount; i++)
        delete requests[i];
    delete[] requests;
    for (int i = 0; i < rideCount; i++)
        delete rides[i];
    delete[] rides;
}

int Simulation::getCapacityEta() { return capacityEta; }
double Simulation::getVelocityGama() { return velocityGama; }
double Simulation::getTimeIntervalDelta() { return timeIntervalDelta; }
double Simulation::getMinEfficiencyLambda() { return minEfficiencyLambda; }
double Simulation::getMaxDistanceBetweenOriginsAlfa() { return maxDistanceBetweenOriginsAlfa; }
double Simulation::getMaxDistanceBetweenDestiniesBeta() { return maxDistanceBetweenDestiniesBeta; }

void Simulation::setCapacityEta(int newCapacityEta) { capacityEta = newCapacityEta; }
void Simulation::setVelocityGama(double newVelocityGama) { velocityGama = newVelocityGama; }
void Simulation::setTimeIntervalDelta(double newTimeIntervalDelta) { timeIntervalDelta = newTimeIntervalDelta; }
void Simulation::setMinEfficiencyLambda(double newMinEfficiencyLambda) { minEfficiencyLambda = newMinEfficiencyLambda; }
void Simulation::setMaxDistanceBetweenOriginsAlfa(double newMaxDistanceBetweenOriginsAlfa) { maxDistanceBetweenOriginsAlfa = newMaxDistanceBetweenOriginsAlfa; }
void Simulation::setMaxDistanceBetweenDestiniesBeta(double newMaxDistanceBetweenDestiniesBeta) { maxDistanceBetweenDestiniesBeta = newMaxDistanceBetweenDestiniesBeta; }

double distance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

bool Simulation::loadInputFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open input file " << filename << std::endl;
        return false;
    }

    int capacityEta;
    file >> capacityEta;

    double velocity;
    file >> velocity;

    double timeInterval;
    file >> timeInterval;

    double originMaxDistance;
    file >> originMaxDistance;

    double destinyMaxDistance;
    file >> destinyMaxDistance;

    double minEfficiency;
    file >> minEfficiency;

    int numRides;
    file >> numRides;

    setCapacityEta(capacityEta);
    setVelocityGama(velocity);
    setTimeIntervalDelta(timeInterval);
    setMaxDistanceBetweenOriginsAlfa(originMaxDistance);
    setMaxDistanceBetweenDestiniesBeta(destinyMaxDistance);
    setMinEfficiencyLambda(minEfficiency);

    if (numRides > MAX_REQUESTS)
    {
        std::cerr << "Error: numRides exceeds system capacity.\n";
        return false;
    }

    for (int i = 0; i < numRides; i++)
    {
        int id;
        double t, ox, oy, dx, dy;

        std::cout << std::fixed << std::setprecision(2);
        if (!(file >> id >> t >> ox >> oy >> dx >> dy))
        {
            std::cerr << "Error: invalid request line " << i << "\n";
            return false;
        }

        ox = this->round5(ox);
        oy = round5(oy);
        dx = round5(dx);
        dy = round5(dy);

        requests[requestCount++] = new Request(id, t, ox, oy, dx, dy);
    }

    file.close();
    return true;
}

void Simulation::initialize()
{
    for (int i = 0; i < requestCount; i++)
    {
        Request *base = requests[i];
        bool rideCreated = false;
        Ride *ride = nullptr;
        int requestController = 0;

        if (base->getState() != REQUESTED)
        {
            continue;
        }
        for (int j = i + 1; j < requestCount; j++)
        {

            if (!rideCreated && requestController >= 1)
            {
                break;
            }

            if (rideCreated)
            {
                if ((ride->getRequestCount() > this->getCapacityEta()))
                {
                    break;
                }

                if (requestController - ride->getRequestCount() == 1)
                {
                    break;
                }
            }
            ++requestController;
            Request *candidate = requests[j];

            double evaluatedTime = candidate->getRequestTime() - base->getRequestTime();

            if (evaluatedTime > timeIntervalDelta)
                break;

            double originDist = distance(base->getOriginX(), base->getOriginY(),
                                         candidate->getOriginX(), candidate->getOriginY());

            double destDist = distance(base->getDestinationX(), base->getDestinationY(),
                                       candidate->getDestinationX(), candidate->getDestinationY());

            if (originDist <= maxDistanceBetweenOriginsAlfa && destDist <= maxDistanceBetweenDestiniesBeta)
            {
                double efficiency = computeEfficiency(base, candidate);

                if (efficiency >= minEfficiencyLambda)
                {
                    if (!rideCreated)
                    {
                        ride = new Ride(rideCount++);
                        ride->addRequest(base);
                        if (ride->getRequestCount() < capacityEta)
                        {
                            candidate->setState(COMBINED);
                            ride->getFirstRequest()->setState(COMBINED);
                            ride->addRequest(candidate);
                        }
                        rideCreated = true;
                    }
                    else
                    {
                        candidate->setState(COMBINED);
                        ride->addRequest(candidate);
                    }
                }
            }
        }

        if (!rideCreated)
        {
            base->setState(INDIVIDUAL);
            ride = new Ride(rideCount++);
            ride->addRequest(base);
        }

        for (int r = 0; r < ride->getRequestCount(); r++)
        {
            Request *req = ride->getRequest(r);
            Stop *pickup = new Stop(req->getOriginX(), req->getOriginY(), PICKUP, req);
            ride->addStop(pickup);
        }

        for (int r = 0; r < ride->getRequestCount(); r++)
        {
            Request *req = ride->getRequest(r);
            Stop *dropoff = new Stop(req->getDestinationX(), req->getDestinationY(), DROPOFF, req);
            ride->addStop(dropoff);
        }

        int stopCount = ride->getStopCount();
        for (int s = 0; s < stopCount - 1; s++)
        {
            Stop *s1 = ride->getStop(s);
            Stop *s2 = ride->getStop(s + 1);

            double dx = s2->getX() - s1->getX();
            double dy = s2->getY() - s1->getY();
            double dist = sqrt(dx * dx + dy * dy);

            ride->addDistance(dist);

            double time = dist / velocityGama;

            Segment *seg = new Segment(
                s1,
                s2,
                time,
                dist,
                (s1->getType() == PICKUP && s2->getType() == PICKUP) ? COLLECTION : (s1->getType() == DROPOFF && s2->getType() == DROPOFF) ? DELIVERY
                                                                                                                                           : TRANSPORT);

            ride->addSegment(seg);
        }

        rides[i] = ride;

        Stop *firstStop = ride->getStop(0);

        scheduler->insertEvent(
            firstStop->getPassenger()->getRequestTime(),
            ride,
            firstStop,
            EVENT_PICKUP);
    }
}

void Simulation::run()
{
    while (!scheduler->isEmpty())
    {
        Event e = scheduler->extractNextEvent();
        currentTime = e.time;

        processEvent(e);
    }
}

void Simulation::processEvent(const Event &e)
{
    Ride *ride = e.ride;
    Stop *stop = e.stop;

    if (ride == nullptr || stop == nullptr)
        return;

    int currentStopIndex = stop->getIndexInRide();
    int totalStops = ride->getStopCount();

    Request *req = stop->getPassenger();

    if (e.type == EVENT_DROPOFF)
    {
        req->setState(COMPLETED);
        req->setCompletionTime(e.time);
    }

    if (currentStopIndex == totalStops - 1)
    {

        double finishTime = e.time;
        double totalDist = ride->getTotalDistance();
        int numStops = ride->getStopCount();

        std::cout << std::fixed << std::setprecision(2);

        std::cout << finishTime << " "
                  << totalDist << " ";

        std::cout << numStops;

        for (int i = 0; i < numStops; i++)
        {
            std::cout << std::fixed << std::setprecision(2);
            Stop *s = ride->getStop(i);
            std::cout << " " << s->getX() << " " << s->getY();
        }

        std::cout << "\n";

        return;
    }

    Stop *nextStop = ride->getStop(currentStopIndex + 1);

    Segment *seg = ride->getSegment(currentStopIndex);

    double arrivalTime = e.time + seg->getTime();

    int nextType = (nextStop->getType() == PICKUP ? EVENT_PICKUP : EVENT_DROPOFF);

    scheduler->insertEvent(
        arrivalTime,
        ride,
        nextStop,
        nextType);
}

double Simulation::computeEfficiency(Request *base, Request *newCandidate)
{
    Stop **stops = new Stop *[4];

    stops[0] = new Stop(base->getOriginX(),
                        base->getOriginY(),
                        PICKUP,
                        base);

    stops[1] = new Stop(newCandidate->getOriginX(),
                        newCandidate->getOriginY(),
                        PICKUP,
                        newCandidate);

    stops[2] = new Stop(base->getDestinationX(),
                        base->getDestinationY(),
                        DROPOFF,
                        base);

    stops[3] = new Stop(newCandidate->getDestinationX(),
                        newCandidate->getDestinationY(),
                        DROPOFF,
                        newCandidate);

    int stopCount = 4;

    double routeDistance = 0.0;
    for (int i = 0; i < stopCount - 1; i++)
    {
        double dx = stops[i + 1]->getX() - stops[i]->getX();
        double dy = stops[i + 1]->getY() - stops[i]->getY();
        routeDistance += sqrt(dx * dx + dy * dy);
    }

    double useful = base->calculateODDistance() + newCandidate->calculateODDistance();

    return useful / routeDistance;
}

double Simulation::round5(double x)
{
    return std::round(x * 100000.0) / 100000.0;
};
