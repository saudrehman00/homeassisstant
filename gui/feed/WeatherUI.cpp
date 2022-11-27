#include "WeatherUI.h"

using namespace std;
using namespace Wt;

WeatherUI::WeatherUI() : WContainerWidget() {
    setHeight(150);
    setStyleClass("text-white d-flex flex-row justify-content-center");

    for (int i = 0; i < 7; i++) {
        WContainerWidget *day = this->addWidget(make_unique<WContainerWidget>());
        day->setStyleClass("text-left mx-4 d-flex flex-column justify-content-between");
        buildFeedItem(day);
        forecast.push_back(day);
    }
}

WeatherUI::~WeatherUI() {}

void WeatherUI::buildFeedItem(WContainerWidget *day) {
    WText *date = day->addWidget(make_unique<WText>("TODAY"));

    WContainerWidget *temperature = day->addWidget(make_unique<WContainerWidget>());
    temperature->setStyleClass("text-left d-flex flex-row");
    
    WImage *image = temperature->addWidget(make_unique<WImage>(WLink("../images/weather/sun.png")));
    image->setWidth(50);
    image->setHeight(50);

    WText *high = temperature->addWidget(make_unique<WText>("MX°"));
    high->setStyleClass("px-3 high-font");
    WText *low = temperature->addWidget(make_unique<WText>("MN°"));
    low->setStyleClass("low-font");

    WText *condition = day->addWidget(make_unique<WText>("SUNNY"));
}