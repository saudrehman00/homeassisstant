#include "SettingsUI.h"

using namespace std;
using namespace Wt;

SettingsUI::SettingsUI() : WTemplate{tr("menupage")} {
    addFunction("tr", &WTemplate::Functions::tr);

    WPushButton *backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
	backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=] {
        this->parent()->removeChild(this);
    });

    WStackedWidget *content = bindWidget("content", make_unique<WStackedWidget>());

    WMenu *sidebar = bindWidget("sidebar", make_unique<WMenu>(content));
    sidebar->addItem("../images/location.png", "Location", make_unique<LocationUI>());
    sidebar->setStyleClass("nav nav-pills flex-column");
}

SettingsUI::~SettingsUI() {}