/* Jun Shao
* 251258566
* November 7 2022
* Main contains the logic for rendering the main application window
* and for interacting with the user input from the UI
*/

#include "Main.h"

using namespace std;
using namespace Wt;

namespace {
    const string OPENSIDEWIDTH = "13%";
    const string CLOSEDSIDEWIDTH = "3.44%";
}

Main::Main(string username) : WTemplate{tr("main")}, username(username) {
    addStyleClass("content-open");
    sideClosed = false;
    app = WApplication::instance();
    app->internalPathChanged().connect(this, &Main::handlePathChange);
    app->setInternalPath("/main");
    
    WLabel *welcome = bindWidget("username", make_unique<WLabel>(username));
    
    WContainerWidget *sidebar = bindWidget("sidebar", make_unique<WContainerWidget>());
    WContainerWidget *backArea = sidebar->addNew<WContainerWidget>();
    backArea->setStyleClass("row d-flex flex-row justify-content-center");

    WPushButton *close = backArea->addNew<WPushButton>();
    close->setStyleClass("btn-close mb-5 mr-5");
    close->clicked().connect([=] {
        if (sideClosed) {
            sideClosed = false;
            sidebar->setWidth(OPENSIDEWIDTH);
            setStyleClass("content-open");
        } else {
            sideClosed = true;
            sidebar->setWidth(CLOSEDSIDEWIDTH);
            setStyleClass("content-closed");
        }
    });

    WPushButton *openListUI = sidebar->addNew<WPushButton>("Notes");
    openListUI->setStyleClass("sidebarbtn");
    openListUI->setIcon("../images/main/list.png");
    openListUI->clicked().connect([=] {
        WDialog* listsWindow = app->root()->addNew<NoteUI>(username);
        listsWindow->show();
    });

    WPushButton *openCalculatorUI= sidebar->addNew<WPushButton>("Calculator");
    openCalculatorUI->setIcon("../images/main/calculator.png");
    openCalculatorUI->setStyleClass("sidebarbtn");
    openCalculatorUI->clicked().connect([=] {
        WDialog* calculatorWindow = app->root()->addNew<CalculatorUI>();
        calculatorWindow->show();
    });

    WPushButton *openConversionUI= sidebar->addNew<WPushButton>("Unit Conversion");
    openConversionUI->setIcon("../images/main/change.png");
    openConversionUI->setStyleClass("sidebarbtn");
    openConversionUI->clicked().connect([=] {
        WDialog* conversionWindow = app->root()->addNew<ConversionUI>();
        conversionWindow->show();
    });

    WPushButton *openClockUI = sidebar->addNew<WPushButton>("Clock");
    openClockUI->setIcon("../images/main/clock.png");
    openClockUI->setStyleClass("sidebarbtn");
    openClockUI->setLink(WLink(LinkType::InternalPath, "/clock"));

    WPushButton *openSettingsUI= sidebar->addNew<WPushButton>("Settings");
    openSettingsUI->setIcon("../images/main/settings.png");
    openSettingsUI->setStyleClass("sidebarbtn");
    openSettingsUI->setLink(WLink(LinkType::InternalPath, "/settings"));

    WPushButton *accountSettingsUI= sidebar->addNew<WPushButton>("Account");
    accountSettingsUI->setIcon("../images/main/settings.png");
    accountSettingsUI->setStyleClass("sidebarbtn");
    accountSettingsUI->setLink(WLink(LinkType::InternalPath, "/account"));

    WContainerWidget *weather = bindWidget("weather", make_unique<WeatherUI>());

    WContainerWidget *news = bindWidget("news", make_unique<NewsUI>());
}

Main::~Main() {}

void Main::handlePathChange() {
    if (app->internalPath() == "/main") {
        this->setHidden(false);
    } else {
        this->setHidden(true);
        if (app->internalPath() == "/clock") {
            app->root()->addNew<ClockUI>();
        } else if (app->internalPath() == "/settings") {
            app->root()->addNew<SettingsUI>();
        } else if (app->internalPath() == "/account") {
            app->root()->addNew<AccountUI>(username);
        }
    }
}