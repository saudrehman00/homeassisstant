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
    addFunction("id", &WTemplate::Functions::id);
    addFunction("tr", &WTemplate::Functions::tr);
    openListUI = bindWidget("openListUI", make_unique<WPushButton>("Lists"));
    openListUI->setStyleClass("btn-square-lists");
    openListUI->clicked().connect([=]{
        app->root()->removeWidget(this);
		app->root()->addNew<ListUI>();
	});
}

Main::~Main() {}