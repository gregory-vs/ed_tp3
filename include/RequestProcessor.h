#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

#include "Request.h"
#include "StreetList.h"
#include "WordIndex.h"
#include <string>

struct Candidate {
    double idLog;
    double distance;
    std::string name;
};

class RequestProcessor {

private:
    StreetList* streets;
    WordIndex* index;

    double computeDistance(double lat1, double long1, double lat2, double long2) const;
    double* intersect(double* a, int aSize, double* b, int bSize, int& outSize) const;
    void sortCandidates(Candidate* arr, int n);
    int processRequest(const Request& req, Candidate*& results);

public:
    RequestProcessor(StreetList* streets, WordIndex* index);
    void processAll(Request* requests, int count, int maxAnswers);
};

#endif
