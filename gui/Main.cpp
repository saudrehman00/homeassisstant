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
    sideClosed = false;

    app->internalPathChanged().connect(this, &Main::handlePathChange);
    app->setInternalPath("/main");
    
    WContainerWidget *sidebar = bindWidget("sidebar", make_unique<WContainerWidget>());
    WContainerWidget *backArea = sidebar->addNew<WContainerWidget>();
    backArea->setStyleClass("row d-flex flex-row justify-content-center");

    WPushButton *close = backArea->addNew<WPushButton>();
    close->setStyleClass("btn-close mb-5 mr-5");
    close->clicked().connect([=] {
        if (sideClosed) {
            sideClosed = false;
            sidebar->setWidth(250);
        } else {
            sideClosed = true;
            sidebar->setWidth(63);
        }
    });

    openListUI = sidebar->addNew<WPushButton>("List");
    openListUI->setStyleClass("sidebarbtn");
    openListUI->setIcon("../images/list.png");
    openListUI->clicked().connect([=] {
        WDialog* listsWindow = app->root()->addNew<ListUI>();
        listsWindow->show();
    });

    openCalculatorUI= sidebar->addNew<WPushButton>("Calculator");
    openCalculatorUI->setIcon("../images/calculator.png");
    openCalculatorUI->setStyleClass("sidebarbtn");
    openCalculatorUI->clicked().connect([=] {
        WDialog* calculatorWindow = app->root()->addNew<CalculatorUI>();
        calculatorWindow->show();
    });

    openConversionUI= sidebar->addNew<WPushButton>("Unit Conversion");
    openConversionUI->setIcon("../images/change.png");
    openConversionUI->setStyleClass("sidebarbtn");
    openConversionUI->clicked().connect([=] {
        WDialog* conversionWindow = app->root()->addNew<ConversionUI>();
        conversionWindow->show();
    });

    openClockUI = sidebar->addNew<WPushButton>("Clock");
    openClockUI->setIcon("../images/clock.png");
    openClockUI->setStyleClass("sidebarbtn");
    openClockUI->setLink(WLink(LinkType::InternalPath, "/clock"));

    openSettingsUI= sidebar->addNew<WPushButton>("Settings");
    openSettingsUI->setIcon("../images/settings.png");
    openSettingsUI->setStyleClass("sidebarbtn");
    openSettingsUI->setLink(WLink(LinkType::InternalPath, "/settings"));
}

Main::~Main() {}

void Main::handlePathChange() {
    Wt::WApplication *app = Wt::WApplication::instance();
    if (app->internalPath() == "/main") {
        this->setHidden(false);
    } else {
        this->setHidden(true);
        if (app->internalPath() == "/clock") {
            app->root()->addNew<ClockUI>();
        } else if (app->internalPath() == "/settings") {
            app->root()->addNew<SettingsUI>();
        }
    }
}

void Main::closeNav() {
}

void Main::openNav() {
    
}