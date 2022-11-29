#include "Note.h"

using std::cerr;
using std::endl;
using std::string;
using std::time_t;
using std::vector;

namespace
{
    /**
     * @brief Get today's date
     * @details Returns the current calendar date string format from time_t
     * @param nothing
     * @return today's date
     */
    string getToday()
    {
        time_t now = time(0);      // gets the current system time
        string time = ctime(&now); // change to c++ string for manipulation
        // remove \n that is generated at the end of a new time_t for formatting
        time.replace(time.length() - 1, time.length(), "\0");
        return time;
    }
}

/**
 * @brief Constructor
 * @details Constructor for a Note object that initializes members but not the date
 * @param type is the note type
 * @param desc is the note contents
 * @return nothing
 */
Note::Note(string type, string desc) : type(type), desc(desc)
{
    dateAdded = getToday();
}

/**
 * @brief Constructor
 * @details Constructor for a Note object that initializes all members
 * @param type is the note type
 * @param desc is the note contents
 * @param date is the date the note was added
 * @return nothing
 */
Note::Note(string type, string desc, string dateAdded) : type(type), desc(desc), dateAdded(dateAdded) {}

/**
 * @brief Default destructor
 * @details Default destructor for a Note object but does not do anything
 * @param nothing
 * @return nothing
 */
Note::~Note() {}

/**
 * @brief Get Note date added
 * @details Returns the current calendar date of when the Note was created
 * @param nothing
 * @return the date the Note was created
 */
string Note::getDateAdded()
{
    return dateAdded;
}

/**
 * @brief Get Note content
 * @details Returns the desc of the Note as a string
 * @param nothing
 * @return the desc of the note as string
 */
string Note::getDesc()
{
    return desc;
}

/**
 * @brief Get Note type
 * @details Returns the type of the Note as a string
 * @param nothing
 * @return the type of the note as string
 */
string Note::getType()
{
    return type;
}

/**
 * @brief Change Note content
 * @details Changes the desc of the Note to a new one
 * @param newDesc is the new desc of the Note
 * @return nothing
 */
void Note::editDesc(string newDesc)
{
    cerr << "desc changed from " + desc + " to " + newDesc << endl;
    desc = newDesc;
}

/**
 * @brief Change Note type
 * @details Changes the type of the Note to a new one
 * @param newType is the new type of the Note
 * @return nothing
 */
void Note::editType(string newType)
{
    cerr << "type changed from " + type + " to " + newType << endl;
    type = newType;
}