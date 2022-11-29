#include "LogMessage.h"
using std::string;

/**
 * @brief Constructor
 * @details Constructor for a LogMessage object, intializing the msg and time
 * @param new_time is the timestamp as string
 * @param new_msg is the message as string
 * @return nothing
 */
LogMessage::LogMessage(string new_time, string new_msg) : time(new_time), msg(new_msg) {}

/**
 * @brief Destructor
 * @details Destructor for a LogMessage object but does not do anything
 * @param nothing
 * @return nothing
 */
LogMessage::~LogMessage() {}

/**
 * @brief Get log message
 * @details Returns the log message that was stored
 * @param nothing
 * @return msg member
 */
string LogMessage::getMessage()
{
    return msg;
}

/**
 * @brief Get log time
 * @details Returns the log time that was stored
 * @param nothing
 * @return time member
 */
string LogMessage::getTime()
{
    return time;
}
