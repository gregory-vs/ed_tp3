#include "InputLoader.h"
#include <iostream>
#include <sstream>

using namespace std;

Address* InputLoader::loadFromCin(int totalLines) {
    Address* list = new Address[totalLines];

    string line;

    for (int i = 0; i < totalLines; i++) {
        getline(cin, line);

        stringstream ss(line);

        string idEndStr, idLogStr, streetType, streetName, number;
        string neighborhood, region, cep, latStr, longStr;

        getline(ss, idEndStr, ';');
        getline(ss, idLogStr, ';');
        getline(ss, streetType, ';');
        getline(ss, streetName, ';');
        getline(ss, number, ';');
        getline(ss, neighborhood, ';');
        getline(ss, region, ';');
        getline(ss, cep, ';');
        getline(ss, latStr, ';');
        getline(ss, longStr, ';');

        list[i] = Address(
            stod(idEndStr),
            stod(idLogStr),
            streetType,
            streetName,
            number,
            neighborhood,
            region,
            cep,
            stod(latStr),
            stod(longStr)
        );
    }

    return list;
}

Request* InputLoader::loadRequestsFromCin(int totalRequests) {
    Request* list = new Request[totalRequests];

    string line;
    for (int i = 0; i < totalRequests; i++) {
        getline(cin, line);
        stringstream ss(line);

        string idReqStr, queryName, latStr, longStr;

        getline(ss, idReqStr, ';');
        getline(ss, queryName, ';');
        getline(ss, latStr,   ';');
        getline(ss, longStr,  ';');

        list[i] = Request(
            stod(idReqStr),
            queryName,
            stod(latStr),
            stod(longStr)
        );
    }

    return list;
}