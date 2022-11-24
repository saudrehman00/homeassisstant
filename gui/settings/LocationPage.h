#ifndef LOCATIONPAGE_H
#define LOCATIONPAGE_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WGoogleMap.h>

class LocationPage : public Wt::WTemplate {
    private:
        Wt::WLabel *help;
        Wt::WGoogleMap *map;
        Wt::WLineEdit *input;
        Wt::WContainerWidget *content;
        void googleMapDoubleClicked(Wt::WGoogleMap::Coordinate c);

    public:
        LocationPage();
        ~LocationPage();
};

#endif