/* Jun Shao
* 251258566
* September 18 2022
* Header file containing member and function delcarations for LogMessage implementation
*/

#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <string>

class LogMessage {
private:
    std::string msg, time;

public:
    LogMessage(std::string new_time, std::string new_msg);
    ~LogMessage();
    std::string getMessage();
    std::string getTime();
};

#endif
