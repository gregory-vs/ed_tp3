#ifndef STREET_H
#define STREET_H

class Street {
private:
    int streetId;         // Unique identifier for the street
    char* type;           // Street type (RUA, AVENIDA, etc.)
    char* name;           // Street name (may contain multiple words)
    char* district;       // Not always unique but stored for reference
    char* region;         // Region of the city

    double meanLatitude;   // Average latitude of all addresses
    double meanLongitude;  // Average longitude of all addresses
    int addressCount;      // Number of addresses used to compute the mean

    char* copyString(const char* s);
    void replaceString(char*& field, const char* value);

public:
    // Constructor
    Street(
        int streetId,
        const char* type,
        const char* name,
        const char* district,
        const char* region
    );

    // Destructor
    ~Street();

    // Add an address coordinate to update meanLat/meanLong
    void addAddressCoordinate(double lat, double lon);

    // Getters
    int getStreetId() const;
    const char* getType() const;
    const char* getName() const;
    const char* getDistrict() const;
    const char* getRegion() const;
    double getMeanLatitude() const;
    double getMeanLongitude() const;
    int getAddressCount() const;

    // Setters
    void setType(const char* value);
    void setName(const char* value);
    void setDistrict(const char* value);
    void setRegion(const char* value);
};

#endif
