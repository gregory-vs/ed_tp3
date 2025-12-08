#include "Street.h"

using namespace std;

Street::Street()
    : idLog(0), streetType(""), streetName(""), 
      avgLatitude(0.0), avgLongitude(0.0) {}

Street::Street(
    double idLog,
    const string& streetType,
    const string& streetName,
    double avgLatitude,
    double avgLongitude
)
    : idLog(idLog),
      streetType(streetType),
      streetName(streetName),
      avgLatitude(avgLatitude),
      avgLongitude(avgLongitude) {}

double Street::getIdLog() const { return idLog; }
string Street::getStreetType() const { return streetType; }
string Street::getStreetName() const { return streetName; }
double Street::getAvgLatitude() const { return avgLatitude; }
double Street::getAvgLongitude() const { return avgLongitude; }

void Street::setIdLog(double value) { idLog = value; }
void Street::setStreetType(const string& value) { streetType = value; }
void Street::setStreetName(const string& value) { streetName = value; }
void Street::setAvgLatitude(double value) { avgLatitude = value; }
void Street::setAvgLongitude(double value) { avgLongitude = value; }

string Street::getFullName() const {
    return streetType + " " + streetName;
}
