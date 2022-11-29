#include "LoginInfo.h"

using std::rotate;
using std::string;

namespace
{
    const double p = 3;

    /**
     * @brief ROT13 encrypt
     * @details Encrypts a string message using a ROT13 cipher
     * @param password is the string to encrypt
     * @return the encrypted password
     */
    string encrypt(string password)
    {
        rotate(password.begin(), password.begin() + 13, password.end());
        return password;
    }

    /**
     * @brief ROT13 decrypt
     * @details Decrypts a string message using a ROT13 cipher
     * @param encryptedPass is the string to dencrypt
     * @return the decrypted password
     */
    string decrypt(string encryptedPass)
    {
        rotate(encryptedPass.begin(), encryptedPass.begin() + encryptedPass.size() - 13, encryptedPass.end());
        return encryptedPass;
    }
}

/**
 * @brief Constructor
 * @details Constructor for a LoginInfo object that initializes members
 * @param username is the session's username
 * @param password is the session's password
 * @return nothing
 */
LoginInfo::LoginInfo(string username, string password) : username(username), db("LoginInfo", "username", {"username", "encryptedPassword"})
{
    encryptedPassword = encrypt(password);
}

/**
 * @brief Default destructor
 * @details Default destructor for a LoginInfo object
 * but does not do anything
 * @param nothing
 * @return nothing
 */
LoginInfo::~LoginInfo() {}

/**
 * @brief Authenticate user info
 * @details Determines if the LoginInfo user info matches 
 * an entry in the database
 * @param nothing
 * @return whether or not the user info is correct
 */
bool LoginInfo::authenticate()
{
    string matchUser = "username=\"" + username + "\"";
    string matchPass = "encryptedPassword=\"" + decrypt(encryptedPassword) + "\"";
    // cerr << "\nLoginInfo: querying db.\n";
    bool correct = false;
    if (db.exists({matchUser, matchPass}))
    {
        correct = true;
    }
    return correct;
}

/**
 * @brief Existence of username
 * @details Determines if the LoginInfo username exists in the database
 * @param nothing
 * @return whether or not the username exists
 */
bool LoginInfo::exists()
{
    return db.exists({"username=\"" + username + "\""});
}

/**
 * @brief Save user info
 * @details Saves the LoginInfo user information to the database
 * @param nothing
 * @return nothing
 */
void LoginInfo::saveData()
{
    db.saveData({username, encryptedPassword});
}

void LoginInfo::delData()
{
}