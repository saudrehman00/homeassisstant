/* Jun Shao
 * 251258566
 * November 7
 * List is an object that contains the logic
 * and data for performing operations on multiple lists
 */

#include "NoteMap.h"

using namespace std;

// ListMap() is the constructor for a ListMap object
// @param nothing
// @return nothing
NoteMap::NoteMap(): db("Lists", {"username", "desc", "type", "dateAdded"}) {}

// ~ListMap() is the destructor for a ListMap object
// @param nothing
// @return nothing
NoteMap::~NoteMap() {}

// work in progress method
void NoteMap::linkProfile(std::string profileName) {

}

// saveData() saves the user's lists to the database
// @param username is the username of this session
// @return nothing
void NoteMap::saveData(std::string username) {
    for (auto& [key, value]: notes) {
        db.saveData({username, value.getDesc(), value.getType(), value.getDateAdded()});
    }
}

// delData() deletes the user's lists from the database
// @param username is the username of this session
// @return nothing
void NoteMap::delData(std::string username) {
    
}

// add() add a list to this map
// @param list is the list to add
// @return nothing
void NoteMap::add(Note list) {
    string key = list.getDateAdded();
	notes.emplace(key, list);
}

// del() delete a list from this map
// @param list is the list to remove
// @return nothing
void NoteMap::del(Note list) {
    string key = list.getDateAdded();
	notes.erase(key);
}

// get() get a list from this map
// @param key is the unique identifier of the list
// @return nothing
Note NoteMap::get(string key) {
    return notes.at(key);
}