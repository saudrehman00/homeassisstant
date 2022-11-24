/* Jun Shao
 * 251258566
 * November 7
 * Header file containing member and function delcarations for Checklist
 */

#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <unordered_map>

class List {
    private:
        std::string type;
        std::string desc;
        std::string schedule;
        std::string dateAdded;
        // link to calendar
        bool repeat;
        bool fav;
        bool done;

    public:
        List(std::string type, std::string desc);
        ~List();
        std::string getScehdule();
        std::string getDateAdded();
        std::string getDesc();
        std::string getType();
        void finish();
        void editDesc(std::string newDesc);
        void editType(std::string newType);
};

#endif