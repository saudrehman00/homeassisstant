#ifndef REQUESTER_H
#define REQUESTER_H

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>

class Request;

class  Requester {
    public:
        virtual void getData(Request* request) = 0;
        std::stringstream makeGetRequest(Request* request);
};

#endif