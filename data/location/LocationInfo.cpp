#include "LocationInfo.h"

using std::string;
using std::to_string;
using std::vector;

/**
 * @brief Constructor
 * @details Constructor for creating a LocationInfo object and initializing members
 * @param username is the session username
 * @return nothing
 */
LocationInfo::LocationInfo(string username) : username(username), db("LocationInfo", "username", {"username", "lat", "lon"})
{
    loadData();
}

/**
 * @brief Default destructor
 * @details Default destructor for deleting a LocationInfo object 
 * but does not do anything
 * @param nothing
 * @return nothing
 */
LocationInfo::~LocationInfo() {}

/**
 * @brief Saves location information
 * @details Saves the currently stored location information of the user to the table
 * @param nothing
 * @return nothing
 */
void LocationInfo::saveData()
{
    db.saveData({username, _lat, _lon});
}

/**
 * @brief Deletes location information
 * @details Deletes the currently stored location information of the user in the table
 * @param nothing
 * @return nothing
 */
void LocationInfo::delData()
{
    db.delData(username);
}

/**
 * @brief Updates location information
 * @details Changes the location information of the user given double format
 * @param lat is the latitude coordinate of the new location
 * @param lon is the longitude coordainte of the new location
 * @return nothing
 */
void LocationInfo::changeLocation(double lat, double lon)
{
    delData();
    _lat = to_string(lat);
    _lon = to_string(lon);
    saveData();
}

/**
 * @brief Updates location information
 * @details Changes the location information of the user given string format
 * @param lat is the latitude coordinate of the new location
 * @param lon is the longitude coordainte of the new location
 * @return nothing
 */
void LocationInfo::changeLocation(string lat, string lon)
{
    delData();
    _lat = lat;
    _lon = lon;
    saveData();
}

/**
 * @brief Loads location information from table
 * @details Loads any previously saved location information of the user from the table
 * @param nothing
 * @return nothing
 */
void LocationInfo::loadData()
{
    vector<vector<string>> lists = db.readAllUser(username);
    if (!lists.empty()) {
        if (!lists.front().empty()) {
            _lon = lists.front().at(0);
            _lat = lists.front().at(1);
        }
    }
}

/**
 * @brief Get latitude
 * @details Gets the latitude coordinate that is currently saved
 * @param nothing
 * @return the latitude coordinate
 */
string LocationInfo::getLat() {
    return _lat;
}

/**
 * @brief Get latitude
 * @details Gets the latitude coordinate that is currently saved
 * @param nothing
 * @return the latitude coordinate
 */
string LocationInfo::getLon() {
    return _lon;
}