/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for Main
*/

#ifndef MAIN_H
#define MAIN_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include "ListUI.h"
#include "clock/ClockUI.h"
#include "settings/SettingsUI.h"
#include "math/CalculatorUI.h"
#include "math/ConversionUI.h"

class Main : public Wt::WTemplate {
    private:
        Wt::WPushButton* openListUI;
        Wt::WPushButton* openClockUI;
        Wt::WPushButton* openSettingsUI;
        Wt::WPushButton* openCalculatorUI;
        Wt::WPushButton* openConversionUI;
        void handlePathChange();
    public:
        Main();
        ~Main();
};

#endif