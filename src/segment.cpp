#include "../include/Segment.h"

Segment::Segment()
{
    startStop = nullptr;
    endStop = nullptr;
    time = 0;
    distance = 0;
    type = TRANSPORT;
}

Segment::Segment(Stop *start, Stop *end, double time, double distance, SegmentType type)
{
    this->startStop = start;
    this->endStop = end;
    this->time = time;
    this->distance = distance;
    this->type = type;
}

Stop *Segment::getStartStop() const { return startStop; }
Stop *Segment::getEndStop() const { return endStop; }
double Segment::getTime() const { return time; }
double Segment::getDistance() const { return distance; }
SegmentType Segment::getType() const { return type; }

void Segment::setStartStop(Stop *start) { this->startStop = start; }
void Segment::setEndStop(Stop *end) { this->endStop = end; }
void Segment::setTime(double time) { this->time = time; }
void Segment::setDistance(double distance) { this->distance = distance; }
void Segment::setType(SegmentType type) { this->type = type; }

std::string Segment::getTypeDescription() const
{
    switch (type)
    {
    case COLLECTION:
        return "Collection segment";
    case DELIVERY:
        return "Delivery segment";
    case TRANSPORT:
        return "Transport segment";
    default:
        return "Unknown segment type";
    }
}
