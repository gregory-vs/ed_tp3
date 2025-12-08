#ifndef INPUTLOADER_H
#define INPUTLOADER_H

#include "Address.h"
#include "Request.h"

class InputLoader {
public:
    static Address* loadFromCin(int totalLines);
    static Request* loadRequestsFromCin(int totalRequests);
};

#endif
