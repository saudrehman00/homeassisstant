#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace curlpp::options;

class WebRequest
{
private:
    std::list<std::string> requestHeaders;
    std::string requestURL;

public:
    WebRequest(std::string hostname);
    WebRequest(std::string hostname, std::list<std::string> header);
    ~WebRequest();
    std::stringstream makeGetRequest();
};

WebRequest::WebRequest(std::string hostname)
// WebRequest::WebRequest(std::string hostname, std::list<std::string> header)
{
    requestURL = hostname;
}

WebRequest::WebRequest(std::string hostname, std::list<std::string> header)
{
    requestURL = hostname;
    requestHeaders = header;
}

WebRequest::~WebRequest()
{
}

std::stringstream WebRequest::makeGetRequest()
{
    std::stringstream ss;
    try
    {
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;

        // Our request to be sent.
        curlpp::Easy myRequest;

        // Set the URL.
        curlpp::options::Url myUrl(requestURL);
        // myRequest.setOpt<curlpp::options::Url>(hostname);
        myRequest.setOpt(new HttpHeader(requestHeaders));
        myRequest.setOpt(myUrl);

        // Send request and get a result.
        // By default the result goes to standard output.
        // myRequest.perform();

        // curlpp::options::WriteStream ws(&os);
        // myRequest.setOpt(ws);
        // myRequest.perform();
        ss << myRequest;

        // boost::property_tree::ptree pt;
        // boost::property_tree::read_json(ss, pt);

        // std::cout << ss.str() << std::endl;
        // std::cout << pt.get_child << std::endl;
    }

    catch (curlpp::RuntimeError &e)
    {
        std::cout << e.what() << std::endl;
    }

    catch (curlpp::LogicError &e)
    {
        std::cout << e.what() << std::endl;
    }
    return ss;
}

int main()
{
    // "lat": 42.9834,
    // "lon": -81.233,
    std::string hostnameW = "https://api.openweathermap.org/data/2.5/forecast?lat=42.9834&lon=-81.233&appid=869a570166961fb2a676c717eb550b92&units=metric";
    WebRequest myWeatherAPICall(hostnameW);
    std::stringstream weatherResult = myWeatherAPICall.makeGetRequest();
    boost::property_tree::ptree ptWeather;
    boost::property_tree::read_json(weatherResult, ptWeather);
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

    std::list<std::string> headers;
    headers.push_back("User-Agent: myproject");
    std::string hostnameN = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
    WebRequest myNewsAPICall(hostnameN, headers);
    std::stringstream newsResult = myNewsAPICall.makeGetRequest();
    boost::property_tree::ptree ptNews;
    boost::property_tree::read_json(newsResult, ptNews);
    auto itN = ptNews;
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        std::cout << it2->first; // [1]
        std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            // std::cout << it3->first; // [1]
            // std::cout << " : " << it3->second.data() << std::endl;
            for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
            {
                if (it4->first == "source")
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "name")
                        {
                            std::cout << it5->first; // [1]
                            std::cout << " : " << it5->second.data() << std::endl;
                        }
                    }
                }
                else if (it4->first == "title")
                {
                    std::cout << it4->first; // [1]
                    std::cout << " : " << it4->second.data() << std::endl;
                }
                else if (it4->first == "urlToImage")
                {
                    std::cout << it4->first; // [1]
                    std::cout << " : " << it4->second.data() << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}