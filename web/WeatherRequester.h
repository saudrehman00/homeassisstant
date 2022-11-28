#ifndef WEATHERREQUESTER_H
#define WEATHERREQUESTER_H

#include "Requester.h"

class Request;

class WeatherRequester : public Requester {
    private:
        std::string host;

    public:
        std::vector<std::vector<std::string>> getData(Request* request);
        std::string getHost();
        WeatherRequester(std::string lat, std::string lon);
        ~WeatherRequester();
};

#endif