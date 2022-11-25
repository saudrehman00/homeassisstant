/* Jun Shao
* 251258566
* November 7 2022
* Main contains the logic for rendering the main application window
* and for interacting with the user input from the UI
*/

#include "Main.h"

using namespace std;
using namespace Wt;

Main::Main() : WTemplate{tr("main")} {
    WApplication *app = WApplication::instance();

    app->internalPathChanged().connect(this, &Main::handlePathChange);
    app->setInternalPath("/main");
    
    openListUI = bindWidget("openListUI", make_unique<WPushButton>("List"));
    openListUI->setIcon("../images/list.png");
    openListUI->clicked().connect([=] {
        WDialog* listsWindow = app->root()->addNew<ListUI>();
        listsWindow->show();
    });

    openCalculatorUI= bindWidget("openCalculatorUI", make_unique<WPushButton>("Calculator"));
    openCalculatorUI->setIcon("../images/calculator.png");
    openCalculatorUI->clicked().connect([=] {
        WDialog* calculatorWindow = app->root()->addNew<CalculatorUI>();
        calculatorWindow->show();
    });

    openConversionUI= bindWidget("openConversionUI", make_unique<WPushButton>("Unit Conversion"));
    openConversionUI->setIcon("../images/change.png");
    openConversionUI->clicked().connect([=] {
        WDialog* conversionWindow = app->root()->addNew<ConversionUI>();
        conversionWindow->show();
    });

    openClockUI = bindWidget("openClockUI", make_unique<WPushButton>("Clock"));
    openClockUI->setIcon("../images/clock.png");
    openClockUI->setLink(WLink(LinkType::InternalPath, "/clock"));

    openSettingsUI= bindWidget("openSettingsUI", make_unique<WPushButton>("Settings"));
    openSettingsUI->setIcon("../images/settings.png");
    openSettingsUI->setLink(WLink(LinkType::InternalPath, "/settings"));
}

Main::~Main() {}

void Main::handlePathChange() {
    Wt::WApplication *app = Wt::WApplication::instance();
    if (app->internalPath() == "/main") {
        app->root()->clear();
        app->root()->addNew<Main>();
    } else if (app->internalPath() == "/clock") {
        this->setHidden(true);
        app->root()->addNew<ClockUI>();
    } else if (app->internalPath() == "/settings") {
        this->setHidden(true);
        app->root()->addNew<SettingsUI>();
    }
}