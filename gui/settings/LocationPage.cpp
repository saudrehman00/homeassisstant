#include "LocationPage.h"

using namespace std;
using namespace Wt;

LocationPage::LocationPage() : WTemplate{tr("locationpage")}
{
    content = bindWidget("content", make_unique<WContainerWidget>());

    map = content->addWidget(make_unique<WGoogleMap>(GoogleMapsVersion::v3));
    map->setMapTypeControl(MapTypeControl::Default);
    map->enableScrollWheelZoom();
    map->enableDoubleClickZoom();
    map->enableDragging();

    map->doubleClicked().connect([=](WGoogleMap::Coordinate c) { 
        this->googleMapDoubleClicked(c);
    });
}

LocationPage::~LocationPage(){};

void LocationPage::googleMapDoubleClicked(WGoogleMap::Coordinate c) {
    std::cerr << "Double clicked at coordinate ("
              << c.latitude() << "," << c.longitude() << ")";
}