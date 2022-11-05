#include "User.h"

using namespace std;

User::User(string name, string pw){
    username = name;
    password = pw;
    userID = -1;
}

User::~User(){
    //cout << "User destructed" << endl;
}

string User::getname(){
    return username;
}

int User::getUID(){
    return userID;
}

void User::assignUID(int ID){
    userID = ID;
}

