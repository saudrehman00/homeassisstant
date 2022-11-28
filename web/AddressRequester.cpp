#include "AddressRequester.h"

using namespace std;

AddressRequester::AddressRequester(string lat, string lon)
{
    host =
        "https://maps.googleapis.com/maps/api/geocode/json?latlng=" + lat + "," + lon + "&key=AIzaSyBsaxHAEYOD0stq-0Smzwr1lGQ14KkOxKg";
}

vector<vector<string>> AddressRequester::getData(Request *request)
{
    boost::property_tree::ptree ptLocation;
    std::stringstream result = Requester::makeGetRequest(request);
    boost::property_tree::read_json(result, ptLocation);
    auto itN = ptLocation;
    vector<vector<string>> all;
    vector<string> location;
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        //  std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            if (it3->first == "compound_code")
            {
                string code = it3->second.data();
                code = code.substr(code.find_first_of(" ") + 1);
                location.push_back(code);
                break;
            }
        }
    }
    all.push_back(location);
    return all;
}

string AddressRequester::getHost()
{
    return host;
}