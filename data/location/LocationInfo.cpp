/* Jun Shao
 * 251258566
 * November 7
 * LoginInfo is an object that contains the logic and data
 * for checking usernames and passwords in the database
 */

#include "LocationInfo.h"

using namespace std;

LocationInfo::LocationInfo(string username) : username(username), db("LocationInfo", "username", {"username", "lat", "lon"})
{
    loadData();
}

LocationInfo::~LocationInfo() {}

void LocationInfo::saveData()
{
    cout << "SAVING:" << endl;
    cout << "lat: " << _lat << endl;
    cout << "lon: " << _lon << endl;
    db.saveData({username, _lat, _lon});
}

void LocationInfo::delData()
{
    db.delData(username);
}

void LocationInfo::changeLocation(double lat, double lon)
{
    delData();
    _lat = to_string(lat);
    _lon = to_string(lon);
    saveData();
}

void LocationInfo::loadData()
{
    vector<vector<string>> lists = db.readAllUser(username);
    if (!lists.empty()) {
        cout << "NOT EMPTY:" << endl;
        _lon = lists.front().at(0);
        _lat = lists.front().at(1);
        cout << "lat: " << _lat << endl;
        cout << "lon: " << _lon << endl;
    }
}

string LocationInfo::getLat() {
    return _lat;
}

string LocationInfo::getLon() {
    return _lon;
}