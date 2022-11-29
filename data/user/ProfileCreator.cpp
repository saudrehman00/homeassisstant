#include "ProfileCreator.h"

using std::string;
using std::cout;
using std::endl;

ProfileCreator::ProfileCreator()
{
}

ProfileCreator::~ProfileCreator()
{
}

int ProfileCreator::createProfile(string name, string pw)
{
    User newUser = User(name, pw);
    userList.push_back(newUser);
    userList.back().assignUID(userList.size());
    cout << name << " has been created." << endl;
    return userList.back().getUID();
}

void ProfileCreator::removeProfile(int uID)
{
    userList.erase(userList.begin() + uID);
}

void ProfileCreator::displayProfile(int uID)
{
    if (uID < userList.size())
    {
        User user1 = userList.at(uID);
        cout << "Displaying user: " << user1.getname() << " with ID: " << user1.getUID() << endl;
    }
    else
    {
        cout << "That is not a valid user ID." << endl;
    }
}