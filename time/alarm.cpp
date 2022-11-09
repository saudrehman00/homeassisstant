#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <thread>
#include <ctime>

int main(){
    std::cout<<"Enter alarm time in format: MMM D YYYY HH:MM:SS\nExample:\nJan 1 2023 06:30:00\n\n";
    std::tm alarmTime;
    std::cin >> std::get_time(&alarmTime, "%b %d %Y %H:%M:%S");
    auto alarm = std::chrono::system_clock::from_time_t(std::mktime(&alarmTime));
    std::time_t alarm_time = std::chrono::system_clock::to_time_t(alarm);
    std::this_thread::sleep_until(alarm);
    std::cout << "\a\a\a\a";
    std::cout << "Alarm!\n\n";
    return 0;
}