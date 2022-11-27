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
NoteMap::NoteMap(std::string username) : db("Notes", "dateAdded", {"username", "desc", "type", "dateAdded"})
{
    this->username = username;
    loadData();
}

// ~ListMap() is the destructor for a ListMap object
// @param nothing
// @return nothing
NoteMap::~NoteMap() {}

// saveData() saves the user's lists to the database
// @param nothing
// @return nothing
void NoteMap::saveData()
{
    for (auto &[key, note] : notes)
    {
        db.saveData({username, note.getDesc(), note.getType(), note.getDateAdded()});
    }
}

// delData() deletes the user's lists from the database
// @param nothing
// @return nothing
void NoteMap::delData()
{
    for (auto &[key, note] : batchToDel)
    {
        db.delData(note.getDateAdded());
    }
}

// loadData() loads the user's old lists from the database
// @param nothing
// @return nothing
void NoteMap::loadData()
{
    vector<vector<string>> lists = db.readAllUser(username);
    for (const auto &row : lists)
    {
        notes.emplace(row[0], Note(row[1], row[2], row[0]));
    }
}

// add() add a note to this map
// @param note is the note to add
// @return nothing
void NoteMap::add(Note note)
{
    string key = note.getDateAdded();
    notes.emplace(key, note);
}

// del() delete a note from this map
// @param note is the note to remove
// @return nothing
void NoteMap::del(Note note)
{
    string key = note.getDateAdded();
    notes.erase(key);
    batchToDel.emplace(key, note);
}

// get() get a note from this map
// @param key is the unique identifier of the note
// @return nothing
Note NoteMap::get(string key)
{
    return notes.at(key);
}

unordered_map<string, Note> NoteMap::getNotes() {
    return this->notes;
}