/* Jun Shao
 * 251258566
 * November 7
 * Header file containing member and function delcarations for Checklist
 */

#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>

class Checklist {
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
        Checklist(std::string type, std::string desc);
        ~Checklist();
        std::string getScehdule();
        std::string getDateAdded();
        std::string getDesc();
        void finish();
        void editDesc(std::string newDesc);
        void editType(std::string newType);
};

#endif