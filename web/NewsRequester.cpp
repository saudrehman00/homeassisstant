#include "NewsRequester.h"
#include "Request.h"

using namespace std;

NewsRequester::NewsRequester() {}

NewsRequester::~NewsRequester() {}

void NewsRequester::getData(Request *request)
{
    boost::property_tree::ptree ptNews;
    std::stringstream result = Requester::makeGetRequest(request);
    boost::property_tree::read_json(result, ptNews);
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
                else if (it4->first == "url")
                {
                    std::cout << it4->first; // [1]
                    std::cout << " : " << it4->second.data() << std::endl;
                }
                else if (it4->first == "urlToImage")
                {
                    std::cout << it4->first; // [1]
                    std::cout << " : " << it4->second.data() << std::endl;
                }
                else if (it4->first == "publishedAt")
                {
                    string date = it4->second.data().substr(0, it4->second.data().find("T"));
                    for (int i = 0; i < date.length(); ++i)
                    {
                        if (date[i] == '-')
                        {

                            date[i] = ' ';
                        }
                    }
                    date = date.substr(date.find_last_of(" ") + 1);
                    std::cout << it4->first; // [1]
                    std::cout << " : " << date << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}
