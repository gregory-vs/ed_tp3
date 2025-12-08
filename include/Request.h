#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    double idRequest;
    std::string queryName;
    double latOrigin;
    double longOrigin;

public:
    // Constructors
    Request();
    Request(
        double idRequest,
        const std::string& queryName,
        double latOrigin,
        double longOrigin
    );

    // Getters
    double getIdRequest() const;
    std::string getQueryName() const;
    double getLatOrigin() const;
    double getLongOrigin() const;

    // Setters
    void setIdRequest(double value);
    void setQueryName(const std::string& value);
    void setLatOrigin(double value);
    void setLongOrigin(double value);
};

#endif
