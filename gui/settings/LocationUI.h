#ifndef LOCATIONUI_H
#define LOCATIONUI_H

#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WGoogleMap.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>

using namespace std;
using namespace Wt;

class LocationUI : public Wt::WContainerWidget {
    private:
        Wt::WGoogleMap *map;
        Wt::WLabel *help;
        Wt::WLineEdit *location;
        Wt::WContainerWidget *top;
        Wt::WPushButton *save;
        Wt::WGoogleMap::Coordinate *c;
        void googleMapClicked(Wt::WGoogleMap::Coordinate c);
        void saveLocation();

    public:
        LocationUI();
        ~LocationUI();
};

#endif