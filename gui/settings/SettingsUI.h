#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTextArea.h>
#include <unordered_map>
#include "LocationUI.h"

class MainUI;

class SettingsUI : public Wt::WTemplate {
    private:
        std::string username;

    public:
        SettingsUI(MainUI *main, string username);
        ~SettingsUI();
        void addObserver(std::string name, Wt::WContainerWidget *c);
};

#endif