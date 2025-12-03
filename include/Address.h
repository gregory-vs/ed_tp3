#ifndef ADDRESS_H
#define ADDRESS_H

class Address {
private:
    char* addressId;   // ID of the specific address
    int   streetId;    // ID of the street (logradouro)
    char* type;        // Street type (RUA, AVENIDA, etc.)
    char* name;        // Street name
    int   number;      // House/building number
    char* district;    // Neighborhood
    char* region;      // City region
    char* cep;         // Postal code
    double latitude;   // Latitude
    double longitude;  // Longitude

    char* copyString(const char* s);
    void replaceString(char*& field, const char* value);

public:
    // Constructor
    Address(
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
    );

    // Destructor
    ~Address();

    // Getters
    const char* getAddressId() const;
    int getStreetId() const;
    const char* getType() const;
    const char* getName() const;
    int getNumber() const;
    const char* getDistrict() const;
    const char* getRegion() const;
    const char* getCep() const;
    double getLatitude() const;
    double getLongitude() const;

    // Setters
    void setAddressId(const char* value);
    void setStreetId(int value);
    void setType(const char* value);
    void setName(const char* value);
    void setNumber(int value);
    void setDistrict(const char* value);
    void setRegion(const char* value);
    void setCep(const char* value);
    void setLatitude(double value);
    void setLongitude(double value);
};

#endif
