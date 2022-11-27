/* Jun Shao
 * 251258566
 * November 7
 * List is an object that contains the logic
 * and data for creating/managing a to do list
 */

#include "Note.h"

using namespace std;

namespace {
    // getToday() gets today's date
    // @param nothing
    // @return nothing
    string getToday() {
        time_t now = time(0); // gets the current system time
        string time = ctime(&now); // change to c++ string for manipulation
        // remove \n that is generated at the end of a new time_t for formatting
        time.replace(time.length()-1, time.length(), "\0");
        return time;
    }
}

// List(type, desc) is the constructor for a List object
// @param type is the type of the list
// @param desc is the list description
// @return nothing
Note::Note(string type, string desc): type(type), desc(desc) {
    dateAdded = getToday();
}

// List(type, desc) is the constructor for a List object
// @param type is the type of the list
// @param desc is the list description
// @param dateAdded is the addition date
// @return nothing
Note::Note(string type, string desc, string dateAdded): type(type), desc(desc), dateAdded(dateAdded) {}

// ~List() is the destructor for a List object
// @param nothing
// @return nothing
Note::~Note() {}

// getDateAdded() gets the date this List was added
// @param nothing
// @return dateAdded is the date the list was added
string Note::getDateAdded() {
    return dateAdded;
}

// getDesc() gets the description of this List
// @param nothing
// @return todo is the description of the item
string Note::getDesc() {
    return desc;
}

// getType() gets the type of this List
// @param nothing
// @return todo is the description of the item
string Note::getType() {
    return type;
}

// editDesc(newDesc) changes the list description to a new one
// @param newDesc is the new list description
// @return nothing
void Note::editDesc(string newDesc) {
    cerr << "\ndesc changed from " + desc + " to " + newDesc + "\n";
    desc = newDesc;
}

// editType(newType) changes the list type to a new one
// @param newType is the new list type
// @return nothing
void Note::editType(string newType) {
    cerr << "\ntype changed from " + type + " to " + newType + "\n";
    type = newType;
}