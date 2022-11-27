/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for Authenticate
*/

#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <functional>
#include "../data/login/LoginInfo.h"
#include "../gui/LoginForm.h"
#include "../gui/Main.h"
#include "../data/logger/Logger.h"

class Authenticate {
    public:
        Authenticate();
        ~Authenticate();
        void startAuth();
};

#endif