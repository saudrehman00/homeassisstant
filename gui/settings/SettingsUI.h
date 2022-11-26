#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTextArea.h>
#include "LocationUI.h"

class SettingsUI : public Wt::WTemplate {
    public:
        SettingsUI();
        ~SettingsUI();
};

#endif