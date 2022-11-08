#include "ListMap.h"

using namespace std;

ListMap::ListMap(): db("Lists", {"username", "desc", "type", "dateAdded"}) {
    
}

// work in progress method
void ListMap::linkProfile(std::string profileName) {

}

// saveData() saves the user's lists to the database
// @param nothing
// @return nothing
void ListMap::saveData() {
    for (const auto& [key, value]: lists) {
        
    }
}