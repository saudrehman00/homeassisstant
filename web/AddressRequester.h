/**
 * @brief Reverse Geolocation API requester.
 * @details Contains the functionalities of sending
 * requests to a reverse geolocation API to obtain address data.
 * @author Jun Shao
 */

#ifndef ADDRESSREQUESTER_H
#define ADDRESSREQUESTER_H

#include <boost/algorithm/string/replace.hpp>
#include "Requester.h"
#include "Request.h"

class AddressRequester : public Requester
{
private:
    std::string host;

public:
    std::vector<std::vector<std::string>> getData(Request *request);
    std::string getHost();
    AddressRequester(std::string lat, std::string lon);
    ~AddressRequester();
};

#endif