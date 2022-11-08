/* Jun Shao
 * 251258566
 * November 7
 * Checklist is an object that contains the logic
 * and data for creating/managing a to do list
 */

#include "Checklist.h"

using namespace std;

namespace {
    string getToday() {
        time_t now = time(0); // gets the current system time
        string time = ctime(&now); // change to c++ string for manipulation
        // remove \n that is generated at the end of a new time_t for formatting
        time.replace(time.length()-1, time.length(), "\0");
        return time;
    }
}

// Checklist(type, desc) is the constructor for a Checklist object
// @param type is the type of the list
// @param desc is the list description
// @return nothing
Checklist::Checklist(string type, string desc): type(type), desc(desc) {
    schedule = "";
    repeat = false;
    fav = false;
    dateAdded = getToday();
}

// ~Checklist() is the destructor for a Checklist object
// @param nothing
// @return nothing
Checklist::~Checklist() {}

// getScehdule() gets the schedule of this Checklist
// @param nothing
// @return schedule of this Checklist
string Checklist::getScehdule() {
    return "today";
}

// getDateAdded() gets the date this Checklist was added
// @param nothing
// @return dateAdded is the date the list was added
string Checklist::getDateAdded() {
    return dateAdded;
}

// getDesc(itemName) gets the description of an item in chkList
// @param nothing
// @return todo is the description of the item
string Checklist::getDesc() {
    return desc;
}

// finish(itemName) marks itemName as complete in this Checklist
// @param nothing
// @return nothing
void Checklist::finish() {
    
}

// editDesc(newDesc) changes the list description to a new one
// @param newDesc is the new list description
// @return nothing
void Checklist::editDesc(string newDesc) {
    cerr << "\ndesc changed from " + desc + " to " + newDesc + "\n";
    desc = newDesc;
}

// editType(newType) changes the list type to a new one
// @param newType is the new list type
// @return nothing
void Checklist::editType(string newType) {
    cerr << "\ntype changed from " + type + " to " + newType + "\n";
    type = newType;
}