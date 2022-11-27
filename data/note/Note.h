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

class Note {
    private:
        std::string type;
        std::string desc;
        std::string dateAdded;

    public:
        Note(std::string type, std::string desc);
        Note(std::string type, std::string desc, std::string dateAdded);
        ~Note();
        std::string getDateAdded();
        std::string getDesc();
        std::string getType();
        void editDesc(std::string newDesc);
        void editType(std::string newType);
};

#endif