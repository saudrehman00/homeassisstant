#include "Requester.h"

using namespace curlpp::options;

int main() 
{

    // "lat": 42.9834,
    // "lon": -81.233,
    // https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}
    /*std::string hostnameW = "https://api.openweathermap.org/data/2.5/weather?lat=42.9834&lon=-81.233&appid=869a570166961fb2a676c717eb550b92";
    NewsRequest myWeatherAPICall(hostnameW);
    myWeatherAPICall.requestData(hostnameW);*/

    std::string hostnameN = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
    NewsRequest myWeatherAPICall(hostnameN);
    myWeatherAPICall.requestData(hostnameN);

    /*std::string hostnameL = "https://maps.googleapis.com/maps/api/geocode/json?address=University%20Western%20Ontario&key=AIzaSyBsaxHAEYOD0stq-0Smzwr1lGQ14KkOxKg";
    WebRequest myNewsAPICall(hostnameL);
    myNewsAPICall.makeGetRequest();*/
}