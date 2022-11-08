/* Jun Shao
* 251258566
* September 18 2022
* Header file containing member and function delcarations for Logger implementation 
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <sqlite3.h>
#include <iostream>
#include <mutex>
#include <memory>
#include "LogMessage.h"
#include "../db/Database.h"

class Logger {
    public:
        static Logger& instance();
        void log(std::string msg);
        std::vector<LogMessage> read_all();

    private:
        Database *_db;
        Logger();
        ~Logger();
        Logger(const Logger& other) = delete;
        Logger& operator=(const Logger& other) = delete;
};

#endif
