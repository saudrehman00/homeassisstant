/* Jun Shao
* 251258566
* November 7
*  Header file containing member and function delcarations for LoginInfo
*/

#ifndef LOGININFO_H
#define LOGININFO_H

#include <string>
#include "../Data.h"

class LoginInfo {
    private:
        // pointer to profile
        std::string username;
        std::string encryptedPassword;
        std::string lastLogin;
        Database db;
        // decrypt();
        // encrypt();
        
    public:
        LoginInfo(std::string username, std::string password);
        ~LoginInfo();
        bool authenticate();
        bool exists();
        std::string getLastLogin();
        void linkProfile(std::string username);
        void saveData();
};

#endif