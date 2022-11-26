/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for Main
*/

#ifndef MAIN_H
#define MAIN_H

#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <any>
#include "NoteUI.h"
#include "clock/ClockUI.h"
#include "settings/SettingsUI.h"
#include "math/CalculatorUI.h"
#include "math/ConversionUI.h"
#include "weather/WeatherUI.h"

class Main : public Wt::WTemplate {
    private:
        Wt::WApplication *app;
        bool sideClosed;
        void handlePathChange();

    public:
        Main();
        ~Main();
};

#endif