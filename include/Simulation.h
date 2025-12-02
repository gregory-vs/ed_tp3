#ifndef SIMULATION_H
#define SIMULATION_H

#include "Scheduler.h"
#include <string>

class Simulation
{
private:
    Scheduler *scheduler;
    Request **requests;
    int requestCount;

    Ride **rides;
    int rideCount;

    double currentTime;

    double totalDistance;
    double totalEfficiency;
    int completedRides;

    int capacityEta;
    double velocityGama;
    double timeIntervalDelta;
    double minEfficiencyLambda;
    double maxDistanceBetweenOriginsAlfa;
    double maxDistanceBetweenDestiniesBeta;

public:
    Simulation();
    ~Simulation();

    bool loadInputFile(const std::string &filename);
    void initialize();
    void run();

    void processEvent(const Event &e);
    void printStatistics() const;

    int getCapacityEta();
    double getVelocityGama();
    double getTimeIntervalDelta();
    double getMinEfficiencyLambda();
    double getMaxDistanceBetweenOriginsAlfa();
    double getMaxDistanceBetweenDestiniesBeta();

    void setCapacityEta(int newCapacityEta);
    void setVelocityGama(double newVelocityGama);
    void setTimeIntervalDelta(double newTimeIntervalDelta);
    void setMinEfficiencyLambda(double minEfficiencyLambda);
    void setMaxDistanceBetweenOriginsAlfa(double maxDistanceBetweenOriginsAlfa);
    void setMaxDistanceBetweenDestiniesBeta(double maxDistanceBetweenDestiniesBeta);
    double computeEfficiency(Request *base, Request *newCandidate);
    double round5(double x);
};

#endif
