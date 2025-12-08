#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

class Address {
private:
    std::string idEnd;
    double idLog;
    std::string streetType;
    std::string streetName;
    std::string number;
    std::string neighborhood;
    std::string region;
    std::string cep;
    double latitude;
    double longitude;

public:
    Address();

    Address(
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
    );

    // Getters
    std::string getIdEnd() const;
    double getIdLog() const;
    std::string getStreetType() const;
    std::string getStreetName() const;
    std::string getNumber() const;
    std::string getNeighborhood() const;
    std::string getRegion() const;
    std::string getCep() const;
    double getLatitude() const;
    double getLongitude() const;

    // Setters
    void setIdEnd(const std::string& value);
    void setIdLog(double value);
    void setStreetType(const std::string& value);
    void setStreetName(const std::string& value);
    void setNumber(const std::string& value);
    void setNeighborhood(const std::string& value);
    void setRegion(const std::string& value);
    void setCep(const std::string& value);
    void setLatitude(double value);
    void setLongitude(double value);

    // Utility
    static void computeAverageCoordinates(
        const Address* list,
        int size,
        double& avgLat,
        double& avgLong
    );
};

#endif
