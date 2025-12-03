#include "Address.h"
#include <cstring>
#include <cstdlib>

// Helper: copy C-string into new memory
char* Address::copyString(const char* s) {
    char* c = (char*) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(c, s);
    return c;
}

// Helper: replace an existing string field
void Address::replaceString(char*& field, const char* value) {
    free(field);
    field = copyString(value);
}

// Constructor
Address::Address(
    const char* addressId,
    int streetId,
    const char* type,
    const char* name,
    int number,
    const char* district,
    const char* region,
    const char* cep,
    double latitude,
    double longitude
) {
    this->addressId = copyString(addressId);
    this->streetId  = streetId;
    this->type      = copyString(type);
    this->name      = copyString(name);
    this->number    = number;
    this->district  = copyString(district);
    this->region    = copyString(region);
    this->cep       = copyString(cep);
    this->latitude  = latitude;
    this->longitude = longitude;
}

// Destructor
Address::~Address() {
    free(addressId);
    free(type);
    free(name);
    free(district);
    free(region);
    free(cep);
}

// Getters
const char* Address::getAddressId() const { return addressId; }
int Address::getStreetId() const { return streetId; }
const char* Address::getType() const { return type; }
const char* Address::getName() const { return name; }
int Address::getNumber() const { return number; }
const char* Address::getDistrict() const { return district; }
const char* Address::getRegion() const { return region; }
const char* Address::getCep() const { return cep; }
double Address::getLatitude() const { return latitude; }
double Address::getLongitude() const { return longitude; }

// Setters
void Address::setAddressId(const char* value) { replaceString(addressId, value); }
void Address::setStreetId(int value) { streetId = value; }
void Address::setType(const char* value) { replaceString(type, value); }
void Address::setName(const char* value) { replaceString(name, value); }
void Address::setNumber(int value) { number = value; }
void Address::setDistrict(const char* value) { replaceString(district, value); }
void Address::setRegion(const char* value) { replaceString(region, value); }
void Address::setCep(const char* value) { replaceString(cep, value); }
void Address::setLatitude(double value) { latitude = value; }
void Address::setLongitude(double value) { longitude = value; }
