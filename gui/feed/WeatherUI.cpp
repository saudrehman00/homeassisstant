#include "WeatherUI.h"

using std::string;
using std::cout;
using std::endl;
using std::make_unique;
using namespace Wt;

namespace
{
    const int HOURLY = 8;
    const int DAILY = 5;
    const int DATELEN = 11;
    const int DATE = 0;
    const int MAX = 1;
    const int MIN = 2;
    const int TYPE = 3;
    const int COND = 4;
}

WeatherUI::WeatherUI(string username) : WContainerWidget(), username(username)
{
    cout << "rendering WeatherUI" << endl;
    setStyleClass("text-white d-flex flex-row justify-content-center w-auto");

    icons["Clouds"] = "../images/weather/cloud.png";
    icons["Rain"] = "../images/weather/rain.png";
    icons["Snow"] = "../images/weather/snow.png";
    icons["Clear"] = "../images/weather/sun.png";

    LocationInfo info(username);
    cout << "got LocationInfo: " << info.getLat() << ", " << info.getLon() << endl;
    if (!info.getLat().empty())
    {
        WeatherRequester *wr = new WeatherRequester(info.getLat(), info.getLon());
        Request r(wr->getHost(), wr);
        weather = r.getData();
        cout << "executed WeatherRequester" << endl;

        if (weather.size() > 0)
        {
            const int LEN = weather.size();
            for (int i = 0; i < LEN; i++)
            {
                cout << "rendering day: 1 of " + LEN << endl;
                if (i % 8 == 0)
                {
                    WContainerWidget *day = this->addWidget(make_unique<WContainerWidget>());
                    day->setStyleClass("text-left mx-4 d-flex flex-column justify-content-between");
                    buildFeedItem(day, i);
                    days.push_back(day);
                }
            }
        }
        else
        {
            this->addWidget(make_unique<WText>("Save your location settings to display weather forecasts."));
        }
    }
    else
    {
        this->addWidget(make_unique<WText>("Save your location settings to display weather forecasts."));
    }
}

WeatherUI::~WeatherUI() {}

void WeatherUI::buildFeedItem(WContainerWidget *day, const int index)
{
    WText *date = day->addWidget(make_unique<WText>(weather[index][DATE].substr(0, DATELEN)));

    WContainerWidget *mid = day->addWidget(make_unique<WContainerWidget>());
    mid->setStyleClass("text-left d-flex flex-row");

    WImage *image = mid->addWidget(make_unique<WImage>(WLink(icons[weather[index][TYPE]])));
    image->setWidth(50);
    image->setHeight(50);

    WContainerWidget *temperature = mid->addWidget(make_unique<WContainerWidget>());
    temperature->setStyleClass("d-flex flex-column text-center");
    WText *high = temperature->addWidget(make_unique<WText>(weather[index][MAX] + "°"));
    high->setStyleClass("px-3 high-font");
    WText *low = temperature->addWidget(make_unique<WText>(weather[index][MIN] + "°"));
    low->setStyleClass("low-font");

    WText *condition = day->addWidget(make_unique<WText>(weather[index][COND]));
}