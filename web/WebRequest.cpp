#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <sstream>
#include <iostream>

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
    void makeGetRequest();
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

void WebRequest::makeGetRequest()
{
    try
    {
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;

        // Our request to be sent.
        curlpp::Easy myRequest;

        // Set the URL.
        curlpp::options::Url myUrl(requestURL);
        // myRequest.setOpt<curlpp::options::Url>(hostname);
        myRequest.setOpt(myUrl);

        // Send request and get a result.
        // By default the result goes to standard output.
        myRequest.perform();
        std::cout << std::endl;
    }

    catch (curlpp::RuntimeError &e)
    {
        std::cout << e.what() << std::endl;
    }

    catch (curlpp::LogicError &e)
    {
        std::cout << e.what() << std::endl;
    }
}

int main()
{
    std::string hostname = "https://example.com";
    WebRequest myTestAPICall(hostname);
    myTestAPICall.makeGetRequest();

    // "lat": 42.9834,
    // "lon": -81.233,
    // https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}
    std::string hostnameW = "https://api.openweathermap.org/data/2.5/weather?lat=42.9834&lon=-81.233&appid=869a570166961fb2a676c717eb550b92";
    WebRequest myWeatherAPICall(hostnameW);
    myWeatherAPICall.makeGetRequest();

    std::string hostnameN = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
    WebRequest myNewsAPICall(hostnameN);
    myNewsAPICall.makeGetRequest();

}