/* Jun Shao
* 251258566
* November 7
* Header file containing member and function delcarations for RealDB
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <sqlite3.h>
#include <iostream>

class Database {
    private:
        sqlite3 *db;
        std::string table;

    public:
        Database(std::string table, std::vector<std::string> attributes);
        ~Database();
        sqlite3* getConnection();
        void saveData(std::vector<std::vector<std::string>> dataRow);
        void saveData(std::vector<std::string> row);
        bool exists(std::string table, std::vector<std::string> row);
};

#endif
