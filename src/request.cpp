#include "Request.h"

Request::Request()
    : idRequest(0), queryName(""),
      latOrigin(0.0), longOrigin(0.0) {}

Request::Request(
    double idRequest,
    const std::string& queryName,
    double latOrigin,
    double longOrigin
)
    : idRequest(idRequest),
      queryName(queryName),
      latOrigin(latOrigin),
      longOrigin(longOrigin) {}

double Request::getIdRequest() const { return idRequest; }
std::string Request::getQueryName() const { return queryName; }
double Request::getLatOrigin() const { return latOrigin; }
double Request::getLongOrigin() const { return longOrigin; }

void Request::setIdRequest(double value) { idRequest = value; }
void Request::setQueryName(const std::string& value) { queryName = value; }
void Request::setLatOrigin(double value) { latOrigin = value; }
void Request::setLongOrigin(double value) { longOrigin = value; }
