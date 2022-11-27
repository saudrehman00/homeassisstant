#ifndef WEATHERUI_H
#define WEATHERUI_H 

#include "Feed.h"

class WeatherUI : public Wt::WContainerWidget, public Feed {
    private:
        std::vector<Wt::WContainerWidget *> forecast;
        void buildFeedItem(Wt::WContainerWidget *day);

    public:
        WeatherUI();
        ~WeatherUI();
};

#endif