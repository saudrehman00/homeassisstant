#ifndef CLOCKPAGE_H
#define CLOCKPAGE_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WTimeEdit.h>

class ClockPage : public Wt::WTemplate {
    private:
        Wt::WContainerWidget* clocks;
        std::string clockName;
        std::string clockFormat;

    public:
        ClockPage(std::string clockName, std::string clockFormat);
        ~ClockPage();
        void showDialog();
};

#endif