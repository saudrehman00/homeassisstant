/* Jun Shao
 * 251258566
 * November 7
 * List is an object that contains the logic
 * and data for performing operations on multiple lists
 */

#include "NoteMap.h"

using namespace std;

// ListMap() is the constructor for a ListMap object
// @param username is the username of the user
// @return nothing
NoteMap::NoteMap(std::string username): db("Notes", "dateAdded", {"username", "desc", "type", "dateAdded"}) {
    this->username = username;
}

// ~ListMap() is the destructor for a ListMap object
// @param nothing
// @return nothing
NoteMap::~NoteMap() {}

// saveData() saves the user's lists to the database
// @param username is the username of this session
// @return nothing
void NoteMap::saveData() {
    for (auto& [key, note]: notes) {
        db.saveData({username, note.getDesc(), note.getType(), note.getDateAdded()});
    }
}

// delData() deletes the user's lists from the database
// @param username is the username of this session
// @return nothing
void NoteMap::delData() {
    for (auto& [key, note]: batchToDel) {
        db.delData(note.getDateAdded());
    }
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
    batchToDel.emplace(key, list);
}

// get() get a list from this map
// @param key is the unique identifier of the list
// @return nothing
Note NoteMap::get(string key) {
    return notes.at(key);
}