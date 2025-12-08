#include "Address.h"

// Constructors
Address::Address()
    : idEnd(""), idLog(0), streetType(""), streetName(""),
      number(""), neighborhood(""), region(""), cep(""),
      latitude(0.0), longitude(0.0) {}

Address::Address(
    const std::string& idEnd,
    double idLog,
    const std::string& streetType,
    const std::string& streetName,
    const std::string& number,
    const std::string& neighborhood,
    const std::string& region,
    const std::string& cep,
    double latitude,
    double longitude
)
    : idEnd(idEnd), idLog(idLog), streetType(streetType),
      streetName(streetName), number(number),
      neighborhood(neighborhood), region(region),
      cep(cep), latitude(latitude), longitude(longitude) {}


// Getters
std::string Address::getIdEnd() const { return idEnd; }
double Address::getIdLog() const { return idLog; }
std::string Address::getStreetType() const { return streetType; }
std::string Address::getStreetName() const { return streetName; }
std::string Address::getNumber() const { return number; }
std::string Address::getNeighborhood() const { return neighborhood; }
std::string Address::getRegion() const { return region; }
std::string Address::getCep() const { return cep; }
double Address::getLatitude() const { return latitude; }
double Address::getLongitude() const { return longitude; }

// Setters
void Address::setIdEnd(const std::string& value) { idEnd = value; }
void Address::setIdLog(double value) { idLog = value; }
void Address::setStreetType(const std::string& value) { streetType = value; }
void Address::setStreetName(const std::string& value) { streetName = value; }
void Address::setNumber(const std::string& value) { number = value; }
void Address::setNeighborhood(const std::string& value) { neighborhood = value; }
void Address::setRegion(const std::string& value) { region = value; }
void Address::setCep(const std::string& value) { cep = value; }
void Address::setLatitude(double value) { latitude = value; }
void Address::setLongitude(double value) { longitude = value; }

void Address::computeAverageCoordinates(
    const Address* list,
    int size,
    double& avgLat,
    double& avgLong
) {
    if (size == 0) {
        avgLat = avgLong = 0.0;
        return;
    }

    double sumLat = 0, sumLong = 0;

    for (int i = 0; i < size; i++) {
        sumLat += list[i].getLatitude();
        sumLong += list[i].getLongitude();
    }

    avgLat = sumLat / size;
    avgLong = sumLong / size;
}
