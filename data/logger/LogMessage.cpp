/* Jun Shao
* 251258566
* September 18 2022
* This file contains the LogMessage object implementation
*/

#include "LogMessage.h"
using namespace std;

// LogMessage(new_time, new_msg) is the constructor for a LogMessage object
// @param new_time new_msg are the initialization values
// @return nothing
LogMessage::LogMessage(string new_time, string new_msg) : time(new_time), msg(new_msg) {}

// ~LogMessage() is the destructor for a LogMessage object
// @param nothing
// @return nothing
LogMessage::~LogMessage() {}

// getMessage() returns the value of the msg data member.
// @param nothing
// @return msg is the log message
string LogMessage::getMessage() {
    return msg;
}

// getTime() returns the value of the time data member.
// @param nothing
// @return time is the log message's recorded time
string LogMessage::getTime() {
    return time;
}
