/**
 * @brief Authentication and management of inputted user information
 * @details Authenticate contains the login to log in users after authentication of input or
 * registers new users by saving to the database
 * @author Jun Shao
 */

#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <functional>
#include "../data/login/LoginInfo.h"
#include "../gui/login/LoginForm.h"
#include "../gui/main/MainUI.h"
#include "../data/logger/Logger.h"

class Authenticate
{
public:
    ~Authenticate();
    void startAuth();
};

#endif