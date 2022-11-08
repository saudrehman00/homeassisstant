/* Jun Shao
* 251258566
* November 7
* An interface containing the implementation for Data objects
*/

#ifndef DATA_H
#define DATA_H

#include "db/Database.h"
#include <string>

class Data {
    public:
        virtual void saveData(std::string username) = 0;
        virtual void delData(std::string username) = 0;
};

#endif