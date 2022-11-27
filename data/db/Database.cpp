/* Jun Shao
 * 251258566
 * November 7
 * This file contains the Database object implementation
 */

#include "Database.h"
using namespace std;

// Database(table, attributes) is the constructor for a Database object
// @param table is the table name of the data
// @param attributes is the column names
// @return nothing
Database::Database(string table, string keyAttribute, vector<string> attributes) : cols(attributes.size()), db(nullptr), table(table), keyAttribute(keyAttribute)
{
    char *err = 0;
    sqlite3_open("Data.db", &db); // open connection to db using its handle
    if (err != SQLITE_OK)
    {
        cerr << "Database - Could not open Database: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cerr << "Database opened."
             << "\n";
    }

    // parsing/formatting the column names as a sql command
    string row; // part of the sql command
    int len = attributes.size();
    for (int i = 0; i < len; i++)
    {
        string s = attributes.back();
        attributes.pop_back();
        row += s + " varchar(255)";
        row += ", ";
    }

    row += "PRIMARY KEY (" + keyAttribute + ")";

    // create a new sqlite table with the name "app" if it does not exist
    string create_table_cmd = "CREATE TABLE IF NOT EXISTS " + table + " (" + row + ")";
    sqlite3_exec(db, create_table_cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "Table construction error: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cerr << "\nTable opened: " + row + "\n";
    }
}

// ~Database() is the destructor for a Database object
// @param nothing
// @return nothing
Database::~Database()
{
    char *err = 0;
    sqlite3_close(db); // close connection to "app" db with its handle
    if (err != SQLITE_OK)
    {
        cerr << "Database - Could not close Data.sql: " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        cerr << "\nDatabase - Data.db terminated and DB closed."
             << "\n";
    }
}

// getConnection() gets the sqlite3 connection to the database
// @param nothing
// @return db the connection to the Data.sql database
sqlite3 *Database::getConnection()
{
    return db;
}

// saveData(data) saves data which represents
// a table in the form of a 2d string array to the database
// @param data is the list of rows of data to be saved
// @return nothing
void Database::saveData(vector<vector<string>> data)
{
    char *err = 0;
    string row = ""; // used for the sql command to insert the row of data

    // parsing/formatting the data entries as a sql command
    int rows = data.size();
    int cols = data[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            string s = data[i].back();
            data.pop_back();
            row += "\"" + s + "\"";
            if (i < cols - 1)
            {
                row += ", ";
            }
        }

        // insert the rows of data into the database
        string cmd = "INSERT INTO " + table + " VALUES (" + row + ")";
        sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

        if (err != SQLITE_OK)
        {
            cerr << "\nDatabase - error executing command: " + cmd + "\n"
                 << sqlite3_errmsg(db) << "\n";
        }
    }
}

// saveData(data) saves data which represents
// a row in the form of a string array to the database
// @param data is the list of data to be saved
// @return nothing
void Database::saveData(vector<string> data)
{
    char *err = 0;
    string row = ""; // used for the sql command to insert the row of data

    // parsing/formatting the data entries as a sql command
    int len = data.size();
    for (int i = 0; i < len; i++)
    {
        string s = data.back();
        data.pop_back();
        row += "\"" + s + "\"";
        if (i < len - 1)
        {
            row += ", ";
        }
    }

    // insert the rows of data into the database
    string cmd = "INSERT INTO " + table + " VALUES (" + row + ")"; // check its inserted in correct order
    sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "\nDatabase - error executing command: " + cmd + "\n"
             << sqlite3_errmsg(db) << "\n";
    }
}

// delData(key) deletes the row of data which has the keyAttribute key
// @param key is the key of the data to be deleted
// @return nothing
void Database::delData(string key)
{
    char *err = 0;
    // insert the rows of data into the database
    string cmd = "DELETE FROM " + table + " WHERE " + keyAttribute + "=" + "'" + key + "'";
    sqlite3_exec(db, cmd.c_str(), nullptr, 0, &err);

    if (err != SQLITE_OK)
    {
        cerr << "\nDatabase - error executing command: " + cmd + "\n"
             << sqlite3_errmsg(db) << "\n";
    }
}

// exists(table, data) determines if an entry of data exists
// @param table is the table of data
// @param data are the matching conditions for the input vs stored data
// @return bool whether or not the data exists in the database
bool Database::exists(string table, vector<string> data)
{
    char *err = 0;
    string cond = ""; // used for the sql command as the SELECT condition

    // parsing/formatting the conditions as a sql command
    int len = data.size();
    for (int i = 0; i < len; i++)
    {
        string s = data.back();
        data.pop_back();
        cond += s;
        if (i < len - 1)
        {
            cond += " AND ";
        }
    }

    // cerr << "\nDatabase: condition is " + cond +"\n";

    string cmd = "SELECT * FROM " + table + " WHERE " + cond;
    sqlite3_stmt *stmnt;

    int result = sqlite3_prepare_v2(db, cmd.c_str(), cmd.length(), &stmnt, nullptr);
    bool found = (sqlite3_step(stmnt) == SQLITE_ROW);
    sqlite3_finalize(stmnt);

    if (found && (result == SQLITE_OK))
    {
        // cerr << "found row from " + cmd + "\n";
    }

    return (found && (result == SQLITE_OK));
}

vector<vector<string>> Database::readAll()
{
    int err = 0;                                  
    string read_all_cmd = "select * from " + table; // sqlite statement to get all data from table
    const int len = read_all_cmd.length();
    sqlite3_stmt *stmnt;
    vector<vector<string>> data; // stores found log messages to be returned

    // query against a Logger's database row by row and store the resulting log message
    err = sqlite3_prepare(db, read_all_cmd.c_str(), len, &stmnt, nullptr);
    if (err != SQLITE_OK)
    {
        cerr << "Could not prepare: " << sqlite3_errmsg(db) << "\n";
    }

    int i = 0;
    while (sqlite3_step(stmnt) == SQLITE_ROW)
    {
        for (int i = 0; i < cols; i++) {
            string cell = (const char *)sqlite3_column_text(stmnt, i);
            data[i].push_back(cell);
        }
    }

    err = sqlite3_finalize(stmnt);
    if (err != SQLITE_OK)
    {
        cerr << "Could not finalize: " << sqlite3_errmsg(db) << "\n";
    }

    return data;
}