#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include <Wt/WTemplate.h>
#include <Wt/WMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTextArea.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include "../../data/Data.h"

class AccountUI : public Wt::WTemplate {
    private:
        bool accountExists();
        Database db;
        Wt::WLineEdit* currentPass;
        Wt::WLineEdit* newPass;
        Wt::WPushButton* okBtn;
        Wt::WPushButton* backBtn;
        Wt::WText* help;
        Wt::WText* title;
        std::string getCurrPass();
        std::string getNewPass();
        std::string username;
        void validatePassword();

    public:
        AccountUI(std::string username);
        ~AccountUI();
};

#endif