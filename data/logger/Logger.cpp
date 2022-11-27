/* Jun Shao
* 251258566
* September 18 2022
* This file contains the Logger object implementation
*/

#include "Logger.h"
using namespace std;

// Scott Meyer's singleton
Logger& Logger::instance() {
    static Logger instance;
    return instance;
}   

// Logger(name) is the constructor for a Logger object
// @param name is the initialization value for app
// @return nothing
Logger::Logger() {
    char *err = 0;
    sqlite3_open("Log.db", &_db); // open connection to db using its handle
    if (err != SQLITE_OK)
    {
        cerr << "Database - Could not open Database: " << sqlite3_errmsg(_db) << "\n";
    }
    else
    {
        cerr << "Database opened."
             << "\n";
    }
    // create a new sqlite table with the name "app" if it does not exist
    string create_table_cmd = "create table if not exists Logger (timestamp varchar(255), message varchar(255))";
    sqlite3_exec(_db, create_table_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK) {
        cerr << "Table construction error: " << sqlite3_errmsg(_db) << "\n";
    }
}

// ~Logger() is the destructor for a Logger object
// @param nothing
// @return nothing
Logger::~Logger() {
    char *err = 0;
    sqlite3_close(_db); // close connection to "app" db with its handle
    if (err != SQLITE_OK)
    {
        cerr << "Logger - Could not close Data.sql: " << sqlite3_errmsg(_db) << "\n";
    }
    else
    {
        cerr << "Logger - Data.db terminated and DB closed."
             << "\n";
    }
}

// log(msg, app) writes msg and the current
// system time to the database in the table called app
// @param msg is the log message
// @return nothing
void Logger::log(string msg) {
    time_t now = time(0); // gets the current system time
    string time = ctime(&now); // change to c++ string for manipulation
    // remove \n that is generated at the end of a new time_t for formatting
    time.replace(time.length()-1, time.length(), "\0");

    // insert the log message into the Logger's database
    string insert_cmd = "insert into Logger values (\"" + time + "\", \"" + msg + "\")";
    char *err = 0;
    sqlite3_exec(_db, insert_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK) {
        cerr << "Logging error: " << sqlite3_errmsg(_db) << "\n";
    }
}

// read_all() returns a vector containing all log messages
// that have been recorded for app in a Logger
// @param nothing
// @return history is a vector containing LogMessage objects
vector<LogMessage> Logger::read_all() {
    int err = 0;  // string pointer used for sqlite errors
    string read_all_cmd = "select * from Logger"; // sqlite statement to get all data from table
    const int len = read_all_cmd.length();
    sqlite3_stmt *stmnt;
    vector<LogMessage> history; // stores found log messages to be returned

    // query against a Logger's database row by row and store the resulting log message
    err = sqlite3_prepare(_db, read_all_cmd.c_str(), len, &stmnt, nullptr);
    if (err != SQLITE_OK) {
        cerr << "Could not prepare: " << sqlite3_errmsg(_db) << "\n";
    }

    while (sqlite3_step(stmnt) == SQLITE_ROW) {
        string time = (const char*) sqlite3_column_text(stmnt, 0);
        string msg = (const char*) sqlite3_column_text(stmnt, 1);
        LogMessage result(time, msg);
        history.push_back(result);
    }

    err = sqlite3_finalize(stmnt);
    if (err != SQLITE_OK) {
        cerr << "Could not finalize: " << sqlite3_errmsg(_db) << "\n";
    }
    
    return history;
}
