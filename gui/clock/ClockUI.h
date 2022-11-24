#ifndef CLOCKUI_H
#define CLOCKUI_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTextArea.h>
#include "ClockPage.h"

class ClockUI : public Wt::WTemplate {
    private:
        Wt::WMenu* sidebar;
        Wt::WStackedWidget* content;
        Wt::WPushButton* backBtn;

    public:
        ClockUI();
        ~ClockUI();
};

#endif