#include "GeoRequester.h"

using namespace std;

GeoRequester::~GeoRequester() {}

GeoRequester::GeoRequester(string location)
{
    boost::replace_all(location, " ", "%20");
    host =
        "https://maps.googleapis.com/maps/api/geocode/json?address=" + location + "&key=AIzaSyBsaxHAEYOD0stq-0Smzwr1lGQ14KkOxKg";
}

vector<vector<string>> GeoRequester::getData(Request *request)
{
    boost::property_tree::ptree ptLocation;
    std::stringstream result = Requester::makeGetRequest(request);
    boost::property_tree::read_json(result, ptLocation);
    auto itN = ptLocation;
    vector<vector<string>> all;
    vector<string> coordinates;
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        // std::cout << it2->first; // [1]
        //  std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            // std::cout << " : " << it3->second.data() << std::endl;
            for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
            {
                if (it4->first == "geometry")
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "location")
                        {
                            for (auto it6 = it5->second.begin(); it6 != it5->second.end(); ++it6)
                            {
                                coordinates.push_back(it6->second.data());
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    all.push_back(coordinates);
    return all;
}

string GeoRequester::getHost()
{
    return host;
}