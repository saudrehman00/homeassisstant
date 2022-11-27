#ifndef WEATHERUI_H
#define WEATHERUI_H 

#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WFont.h>
#include <vector>

class WeatherUI : public Wt::WContainerWidget {
    private:
        std::vector<Wt::WContainerWidget *> forecast;
        void buildDay(Wt::WContainerWidget *day);

    public:
        WeatherUI();
        ~WeatherUI();
};

#endif