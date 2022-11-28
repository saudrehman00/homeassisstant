#ifndef LOCATIONINFO_H
#define LOCATIONINFO_H

#include <string>
#include "../Data.h"

class LocationInfo : public Data {
    private:
        std::string username;
        std::string _lat;
        std::string _lon;
        Database db;
        
    public:
        LocationInfo(std::string username);
        ~LocationInfo();
        std::string getLat();
        std::string getLon();
        void changeLocation(double lat, double lon);
        void saveData();
        void delData();
        void loadData();
};

#endif