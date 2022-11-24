#include "SettingsUI.h"

using namespace std;
using namespace Wt;

SettingsUI::SettingsUI() : WTemplate{tr("menupage")} {
    addFunction("tr", &WTemplate::Functions::tr);

    backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
	backBtn->setLink(WLink(LinkType::InternalPath, "/main"));

    content = bindWidget("content", make_unique<WStackedWidget>());

    sidebar = bindWidget("sidebar", make_unique<WMenu>(content));
    sidebar->addItem("../images/location.png", "Location", make_unique<LocationPage>());
    sidebar->setStyleClass("nav nav-pills flex-column");
}

SettingsUI::~SettingsUI() {}