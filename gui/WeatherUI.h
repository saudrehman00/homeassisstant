#ifndef WEATHERUI_H
#define WEATHERUI_H 

#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>

class WeatherUI : public Wt::WTemplate {
    public:
        WeatherUI();
        ~WeatherUI();
};

#endif