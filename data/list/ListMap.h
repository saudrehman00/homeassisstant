#ifndef LISTMAP_H
#define LISTMAP_h

#include <unordered_map>
#include <string>
#include "Checklist.h"
#include "Data.h"

class ListMap : public Data {
    private:
        std::unordered_map<std::string, Checklist> lists;
        Database db;
        // pointer to user

    public:
        ListMap();
        ~ListMap();
        void linkProfile(std::string profileName);
        void saveData();
};
#endif