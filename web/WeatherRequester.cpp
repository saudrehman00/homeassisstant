#include "WeatherRequester.h"
#include "Request.h"

using namespace std;

WeatherRequester::WeatherRequester() {}

WeatherRequester::~WeatherRequester() {}


void WeatherRequester::getData(Request* request) {
    boost::property_tree::ptree ptWeather;
    std::stringstream result = Requester::makeGetRequest(request);
    boost::property_tree::read_json(result, ptWeather);
    auto itW = ptWeather.get_child("list");
    for (auto it2 = itW.begin(); it2 != itW.end(); ++it2)
    {
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            if (it3->first == "dt")
            {
                std::cout << it3->first; // [1]
                std::cout << " : " << it3->second.data();
                time_t rawtime;
                rawtime = strtoul(it3->second.data().c_str(), NULL, 0);
                std::cout << " : " << std::put_time(std::localtime(&rawtime), "%c %Z") << std::endl;
            }
            else if (it3->first == "main")
            {
                std::cout << it3->first; // [1]
                std::cout << " : " << it3->second.data() << std::endl;
                for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
                {
                    if (it4->first == "temp")
                    {
                        std::cout << "\t" << it4->first; // [1]
                        std::cout << " : " << it4->second.data() << std::endl;
                    }
                    else if (it4->first == "feels_like")
                    {
                        std::cout << "\t" << it4->first; // [1]
                        std::cout << " : " << it4->second.data() << std::endl;
                    }
                }
            }

            else if (it3->first == "weather")
            {
                std::cout << it3->first << " :" << std::endl;
                for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "main")
                        {
                            std::cout << "\t" << it5->first; // [1]
                            std::cout << " : " << it5->second.data() << std::endl;
                        }
                        if (it5->first == "description")
                        {
                            std::cout << "\t" << it5->first; // [1]
                            std::cout << " : " << it5->second.data() << std::endl;
                        }
                    }
                }
            }
        }
        // [2]
        std::cout << std::endl;
    }
}
