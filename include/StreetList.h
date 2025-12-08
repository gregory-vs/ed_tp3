#ifndef STREETLIST_H
#define STREETLIST_H

#include "AddressList.h"
#include "Street.h"
#include <string>

struct StreetAccumulator {
    double idLog;
    std::string streetType;
    std::string streetName;

    double sumLat;
    double sumLong;
    int count;
};

class StreetList {
private:
    Street* list;           // final list of unique streets
    int size;               // number of unique streets

    StreetAccumulator* acc; // temporary accumulator array
    int accSize;            // number of accumulators
    int accCapacity;        // dynamic capacity

    void expandAcc();       // expand accumulator array
    int findAcc(double idLog) const; // locate accumulator by idLog

public:
    StreetList();
    ~StreetList();

    // Build from the address list
    void buildFromAddressList(AddressList& addresses);

    // Getters
    Street* getList() const;
    int getSize() const;

    // Utility
    Street getAt(int index) const;
};

#endif
