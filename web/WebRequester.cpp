#include "WeatherRequester.h"
#include "NewsRequester.h"
#include "Request.h"

using namespace curlpp::options;

int main()
{
    // "lat": 42.9834,
    // "lon": -81.233,
    std::string hostnameW = "https://api.openweathermap.org/data/2.5/forecast?lat=42.9834&lon=-81.233&appid=869a570166961fb2a676c717eb550b92&units=metric";
    Request r(hostnameW, new WeatherRequester);
    r.getData();

    std::list<std::string> headers;
    headers.push_back("User-Agent: myproject");
    std::string hostnameN = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
    r.setHeaders(headers);
    r.setHost(hostnameN);
    r.setRequester(new NewsRequester);
    r.getData();
}