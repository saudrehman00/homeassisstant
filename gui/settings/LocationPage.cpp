#include "LocationPage.h"

using namespace std;
using namespace Wt;

LocationPage::LocationPage() : WTemplate{tr("locationpage")}
{
    addFunction("tr", &WTemplate::Functions::tr);
    
    content = bindWidget("content", make_unique<WContainerWidget>());
    content->setStyleClass("mx-5");
    
    help = content->addWidget(make_unique<WLabel>("You can enter your location information to utilize location services such as seeing the weather."));

    input = content->addWidget(make_unique<WLineEdit>());
    input->setPlaceholderText("Enter a location...");

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