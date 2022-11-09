/* Jun Shao
 * 251258566
 * November 7
 * List is an object that contains the logic
 * and data for performing operations on multiple lists
 */

#include "ListMap.h"

using namespace std;

// ListMap() is the constructor for a ListMap object
// @param nothing
// @return nothing
ListMap::ListMap(): db("Lists", {"username", "desc", "type", "dateAdded"}) {}

// ~ListMap() is the destructor for a ListMap object
// @param nothing
// @return nothing
ListMap::~ListMap() {}

// work in progress method
void ListMap::linkProfile(std::string profileName) {

}

// saveData() saves the user's lists to the database
// @param username is the username of this session
// @return nothing
void ListMap::saveData(std::string username) {
    for (auto& [key, value]: lists) {
        db.saveData({username, value.getDesc(), value.getType(), value.getDateAdded()});
    }
}

// delData() deletes the user's lists from the database
// @param username is the username of this session
// @return nothing
void ListMap::delData(std::string username) {
    
}

// add() add a list to this map
// @param list is the list to add
// @return nothing
void ListMap::add(List list) {
    string key = list.getDateAdded();
	lists.emplace(key, list);
}

// del() delete a list from this map
// @param list is the list to remove
// @return nothing
void ListMap::del(List list) {
    string key = list.getDateAdded();
	lists.erase(key);
}

// get() get a list from this map
// @param key is the unique identifier of the list
// @return nothing
List ListMap::get(string key) {
    return lists.at(key);
}