/* Jun Shao
 * 251258566
 * November 7
 * Header file containing member and function delcarations for ListMap
 */

#ifndef LISTMAP_H
#define LISTMAP_h

#include <unordered_map>
#include <string>
#include "List.h"
#include "../Data.h"

class ListMap : public Data {
    private:
        std::unordered_map<std::string, List> lists;
        Database db;
        // pointer to user

    public:
        ListMap();
        ~ListMap();
        void linkProfile(std::string profileName);
        void saveData(std::string username);
        void delData(std::string username);
        void add(List list);
        void del(List list);
        List get(std::string key);
};
#endif