#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "User.h"

#ifndef PROFILECREATOR_H
#define PROFILECREATOR_H

class ProfileCreator{
    private:
        std::vector<User> userList;
    public:
        ProfileCreator();
        ~ProfileCreator();
        int createProfile(std::string name, std::string password);
        void removeProfile(int userID);
        void displayProfile(int userID);
};

#endif