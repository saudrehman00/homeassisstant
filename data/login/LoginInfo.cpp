/* Jun Shao
* 251258566
* November 7
* LoginInfo is an object that contains the logic and data 
* for checking usernames and passwords in the database
*/

#include "LoginInfo.h"

using namespace std;

namespace {
    // work in progress method
    string encrypt(string password) {
        return "a";
    }

    // work in progress method
    string decrypt(string encryptedPass) {
        return "a";
    }

    // loginTime() gets the current system time
    // @param nothing
    // @return time is the current system time
    string loginTime() {
        time_t now = time(0); // gets the current system time
        string time = ctime(&now); // change to c++ string for manipulation
        // remove \n that is generated at the end of a new time_t for formatting
        time.replace(time.length()-1, time.length(), "\0");
        return time;
    }
}

// LoginInfo(username, password) is the constructor for a LoginInfo object
// @param nothing
// @return nothing
LoginInfo::LoginInfo(string username, string password): username(username), db("LoginInfo", {"username", "encryptedPassword"}) {
    encryptedPassword = encrypt(password);
    lastLogin = "";
}

// ~LoginInfo() is the destructor for a LoginInfo object
// @param nothing
// @return nothing
LoginInfo::~LoginInfo() {}


// getLastLogin() gets the last login time of the user
// @param nothing
// @return lastLogin is the last login time of the logged user
string LoginInfo::getLastLogin() {
    return lastLogin;
}

// authenticate() determines the validity of
//  the user credentials based on their inputted username and password
// @param nothing
// @return exists if the user credentials are correct
bool LoginInfo::authenticate() {
    string matchUser = "username=\"" + username + "\"";
    string matchPass = "encryptedPassword=\"" + encryptedPassword + "\"";
    // cerr << "\nLoginInfo: querying db.\n";
    bool correct = false;
    if (db.exists("LoginInfo", {matchUser, matchPass})) {
        lastLogin = loginTime();
        correct = true;
    }
    return correct;
}

// exists() determines if the username exists in the database
// @param nothing
// @return bool whether or not the username is saved
bool LoginInfo::exists() {
    return db.exists("LoginInfo", {"username=\"" + username + "\""});
}

// work in progress method
void LoginInfo::linkProfile(std::string profileName) {

}

// saveData() saves the username and encryptedPassword to the database
// @param nothing
// @return nothing
void LoginInfo::saveData() {
    db.saveData({username, encryptedPassword});
}