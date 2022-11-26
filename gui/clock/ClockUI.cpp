#include "ClockUI.h"

using namespace std;
using namespace Wt;

ClockUI::ClockUI() : WTemplate{tr("menupage")} {
    addFunction("tr", &WTemplate::Functions::tr);

    WPushButton *backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
	backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=] {
        this->parent()->removeChild(this);
    });

    WStackedWidget *content = bindWidget("content", make_unique<WStackedWidget>());

    WMenu *sidebar = bindWidget("sidebar", make_unique<WMenu>(content));
    sidebar->addItem("../images/timer.png", "Timer", make_unique<ClockPage>("Timer", "hh:mm:ss"));
    sidebar->addItem("../images/alarm.png", "Alarm", make_unique<ClockPage>("Alarm", "h:mm:ss AP"));
    sidebar->setStyleClass("nav nav-pills flex-column");
}

ClockUI::~ClockUI() {}