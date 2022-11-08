#include <stdio.h>
#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

class User{
    private:
        std::string username;
        std::string password;
        int userID;    
    public:
        User(std::string name, std::string password);
        ~User();
        std::string getname();
        int getUID();
        void assignUID(int ID);

};

#endif

