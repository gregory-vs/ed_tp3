#ifndef SEGMENT_H
#define SEGMENT_H

#include "Stop.h"

enum SegmentType
{
    COLLECTION,
    DELIVERY,
    TRANSPORT
};

class Segment
{
private:
    Stop *startStop;
    Stop *endStop;
    double time;
    double distance;
    SegmentType type;

public:
    Segment();
    Segment(Stop *start, Stop *end, double time, double distance, SegmentType type);

    Stop *getStartStop() const;
    Stop *getEndStop() const;
    double getTime() const;
    double getDistance() const;
    SegmentType getType() const;

    void setStartStop(Stop *start);
    void setEndStop(Stop *end);
    void setTime(double time);
    void setDistance(double distance);
    void setType(SegmentType type);

    std::string getTypeDescription() const;
};

#endif
