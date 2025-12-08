#ifndef STREET_H
#define STREET_H

#include <string>

class Street {
private:
    double idLog;
    std::string streetType;
    std::string streetName;
    double avgLatitude;
    double avgLongitude;

public:
    // Constructors
    Street();
    Street(
        double idLog,
        const std::string& streetType,
        const std::string& streetName,
        double avgLatitude,
        double avgLongitude
    );

    // Getters
    double getIdLog() const;
    std::string getStreetType() const;
    std::string getStreetName() const;
    double getAvgLatitude() const;
    double getAvgLongitude() const;

    // Setters
    void setIdLog(double value);
    void setStreetType(const std::string& value);
    void setStreetName(const std::string& value);
    void setAvgLatitude(double value);
    void setAvgLongitude(double value);

    // Utility: returns the full street name (e.g., "RUA ADEMAR PIMENTA BRANT")
    std::string getFullName() const;
};

#endif
