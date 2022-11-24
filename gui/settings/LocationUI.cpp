#include "LocationUI.h"

using namespace std;
using namespace Wt;

LocationUI::LocationUI() : WContainerWidget() {
    WVBoxLayout *layout = setLayout(make_unique<WVBoxLayout>());
    setHeight(900);

    top = layout->addWidget(make_unique<WContainerWidget>());
    top->setStyleClass("mx-5");
    help = top->addWidget(make_unique<WLabel>("Enter your location information or click on the map to utilize location services such as showing the weather."));
    location = top->addWidget(make_unique<WLineEdit>());
    location->setWidth(500);
    save = top->addWidget(make_unique<WPushButton>("Save"));
    
    map = layout->addWidget(make_unique<WGoogleMap>(GoogleMapsVersion::v3));
    map->setMapTypeControl(MapTypeControl::Default);
    map->enableScrollWheelZoom();
    map->enableDoubleClickZoom();
    map->enableDragging();
    map->clicked().connect([=] (WGoogleMap::Coordinate c) { 
        this->googleMapClicked(c); 
    });
    map->setStyleClass("mx-5 mt-3");

    location->setPlaceholderText("Enter a location...");
}

LocationUI::~LocationUI() {}

void LocationUI::googleMapClicked(WGoogleMap::Coordinate c) {
    map->clearOverlays();
    map->addMarker(WGoogleMap::Coordinate(c.latitude(), c.longitude()));
    this->c->setLatitude(c.latitude());
    this->c->setLongitude(c.longitude());
}

void LocationUI::saveLocation() {
    
}

