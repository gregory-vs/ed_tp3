#include "Street.h"
#include <cstring>
#include <cstdlib>

// Helper to copy string
char* Street::copyString(const char* s) {
    char* c = (char*) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(c, s);
    return c;
}

// Helper to replace existing string
void Street::replaceString(char*& field, const char* value) {
    free(field);
    field = copyString(value);
}

// Constructor
Street::Street(
    int streetId,
    const char* type,
    const char* name,
    const char* district,
    const char* region
) {
    this->streetId = streetId;
    this->type = copyString(type);
    this->name = copyString(name);
    this->district = copyString(district);
    this->region = copyString(region);

    this->meanLatitude = 0.0;
    this->meanLongitude = 0.0;
    this->addressCount = 0;
}

// Destructor
Street::~Street() {
    free(type);
    free(name);
    free(district);
    free(region);
}

// Add coordinate → incrementally update the mean
void Street::addAddressCoordinate(double lat, double lon) {
    addressCount++;

    // Incremental average:
    meanLatitude  += (lat - meanLatitude) / addressCount;
    meanLongitude += (lon - meanLongitude) / addressCount;
}

// Getters
int Street::getStreetId() const { return streetId; }
const char* Street::getType() const { return type; }
const char* Street::getName() const { return name; }
const char* Street::getDistrict() const { return district; }
const char* Street::getRegion() const { return region; }
double Street::getMeanLatitude() const { return meanLatitude; }
double Street::getMeanLongitude() const { return meanLongitude; }
int Street::getAddressCount() const { return addressCount; }

// Setters
void Street::setType(const char* value) { replaceString(type, value); }
void Street::setName(const char* value) { replaceString(name, value); }
void Street::setDistrict(const char* value) { replaceString(district, value); }
void Street::setRegion(const char* value) { replaceString(region, value); }
