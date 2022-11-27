#ifndef WEATHERREQUESTER_H
#define WEATHERREQUESTER_H

#include "Requester.h"

class Request;

class WeatherRequester : public Requester {
    public:
        void getData(Request* request);
        WeatherRequester();
        ~WeatherRequester();
};

#endif