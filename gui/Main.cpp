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