#include "NewsRequester.h"
#include "Request.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace
{
    string clean(string date)
    {
        replace(date.begin(), date.end(), 'T', ' ');
        date.erase(remove(date.begin(), date.end(), 'Z'), date.end());

        // boost utc to local conversion: https://www.boost.org/doc/libs/1_31_0/libs/date_time/doc/exp-local_utc_conversion.html
        // eastern timezone is utc-5
        typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
        ptime t(time_from_string(date));
        ptime est = us_eastern::utc_to_local(t);
        date = to_simple_string(est);
        string cal, time;
        stringstream s(date);
        s >> cal >> time;
        time = time.substr(0, time.find_last_of(':'));
        cal = cal.substr(cal.find("-") + 1);
        replace(cal.begin(), cal.end(), '-', ' ');
        return cal + " " + time;
    }
}

NewsRequester::NewsRequester()
{
    headers.push_back("User-Agent: myproject");
    host = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
}

NewsRequester::~NewsRequester() {}

vector<vector<string>> NewsRequester::getData(Request *request)
{
    boost::property_tree::ptree ptNews;
    std::stringstream result = Requester::makeGetRequest(request);
    boost::property_tree::read_json(result, ptNews);
    auto itN = ptNews;
    vector<vector<string>> all;
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        //std::cout << it2->first; // [1]
        // std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            vector<string> article;
            // std::cout << " : " << it3->second.data() << std::endl;
            for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
            {
                if (it4->first == "source")
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "name")
                        {
                            // std::cout << it5->first; // [1]
                            article.push_back(it5->second.data());
                        }
                    }
                }
                else if (it4->first == "title")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "url")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "urlToImage")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "publishedAt")
                {
                    article.push_back(clean(it4->second.data()));
                }
            }
            all.push_back(article);
        }
    }
    return all;
}

string NewsRequester::getHost()
{
    return host;
}

std::list<std::string> NewsRequester::getHeaders()
{
    return headers;
}
