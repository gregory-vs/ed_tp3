#include "StreetList.h"
#include <iostream>

StreetList::StreetList() {
    list = nullptr;
    size = 0;

    accCapacity = 10;
    accSize = 0;
    acc = new StreetAccumulator[accCapacity];
}

StreetList::~StreetList() {
    delete[] list;
    delete[] acc;
}

void StreetList::expandAcc() {
    accCapacity *= 2;
    StreetAccumulator* newAcc = new StreetAccumulator[accCapacity];

    for (int i = 0; i < accSize; i++) {
        newAcc[i] = acc[i];
    }

    delete[] acc;
    acc = newAcc;
}

int StreetList::findAcc(double idLog) const {
    for (int i = 0; i < accSize; i++) {
        if (acc[i].idLog == idLog)
            return i;
    }
    return -1;
}

void StreetList::buildFromAddressList(AddressList& addresses) {
    int n = addresses.getSize();
    Address* addr = addresses.getList();

    for (int i = 0; i < n; i++) {
        double idLog = addr[i].getIdLog();
        int pos = findAcc(idLog);

        if (pos == -1) {
            if (accSize == accCapacity)
                expandAcc();

            pos = accSize;
            accSize++;

            acc[pos].idLog = idLog;
            acc[pos].streetType = addr[i].getStreetType();
            acc[pos].streetName = addr[i].getStreetName();
            acc[pos].sumLat = 0;
            acc[pos].sumLong = 0;
            acc[pos].count = 0;
        }

        acc[pos].sumLat += addr[i].getLatitude();
        acc[pos].sumLong += addr[i].getLongitude();
        acc[pos].count++;
    }

    size = accSize;
    list = new Street[size];

    for (int i = 0; i < size; i++) {
        double avgLat = acc[i].sumLat / acc[i].count;
        double avgLong = acc[i].sumLong / acc[i].count;

        list[i] = Street(
            acc[i].idLog,
            acc[i].streetType,
            acc[i].streetName,
            avgLat,
            avgLong
        );
    }
}

Street* StreetList::getList() const {
    return list;
}

int StreetList::getSize() const {
    return size;
}

Street StreetList::getAt(int index) const {
    if (index < 0 || index >= size)
        return Street();
    return list[index];
}
