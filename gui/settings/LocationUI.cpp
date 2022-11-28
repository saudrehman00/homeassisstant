#include "LocationUI.h"

using namespace std;
using std::find;
using namespace Wt;

LocationUI::LocationUI(string username) : WContainerWidget(), username(username) 
{
    setHeight(900);
    WLabel *help = this->addWidget(make_unique<WLabel>("Enter your location information, or click on the map, and press save to utilize location services such as showing the weather."));
    help->setStyleClass("text-white mt-4 mx-5");
    WContainerWidget *top = this->addWidget(make_unique<WContainerWidget>());
    top->setStyleClass("mx-5 mt-5 d-flex flex-row");
    WLineEdit *location = top->addWidget(make_unique<WLineEdit>());
    location->setWidth(500);
    location->enterPressed().connect([=] {
        this->pan(location->text().toUTF8());
    });
    auto validator = make_shared<WValidator>(true);
    location->setValidator(validator);

    WPushButton *view = top->addWidget(make_unique<WPushButton>("View on map"));
    view->clicked().connect([=] {
        this->pan(location->text().toUTF8());
    });

    WPushButton *save = top->addWidget(make_unique<WPushButton>("Save"));
    save->clicked().connect([=] {
        pan(location->text().toUTF8());
        this->saveLocation();
    });
    save->setStyleClass("mx-5");

    location->setPlaceholderText("Enter a location...");

    WContainerWidget *maparea = this->addWidget(make_unique<WContainerWidget>());
    maparea->setHeight(900);
    WVBoxLayout *layout = maparea->setLayout(make_unique<WVBoxLayout>());
    map = layout->addWidget(make_unique<WGoogleMap>(GoogleMapsVersion::v3));
    map->setMapTypeControl(MapTypeControl::Default);
    map->enableScrollWheelZoom();
    map->enableDoubleClickZoom();
    map->enableDragging();
    map->clicked().connect([=] (WGoogleMap::Coordinate c) { 
        this->googleMapClicked(c); 
    });
    map->setStyleClass("mx-3 mt-3");
}

LocationUI::~LocationUI() {}

void LocationUI::googleMapClicked(WGoogleMap::Coordinate c) {
    map->clearOverlays();
    map->addMarker(WGoogleMap::Coordinate(c.latitude(), c.longitude()));
    _lat = c.latitude();
    _lon = c.longitude();
    cout << "MAPS COORDINATE SAVE:" << endl;
    cout << "lat: " << _lat << endl;
    cout << "lon: " << _lon << endl;
}

void LocationUI::saveLocation() {
    LocationInfo l(username);
    l.changeLocation(_lat, _lon);
    this->notify();
}

void LocationUI::pan(string location) {
    GeoRequester *gr = new GeoRequester(location);
    Request r(gr->getHost(), gr);
    vector<vector<string>> loc = r.getData();

    if (loc.size() > 0) {
        double lat = stod(loc[0][0]);
        double lon = stod(loc[0][1]);
        map->panTo(WGoogleMap::Coordinate(lat, lon));
        map->addMarker(WGoogleMap::Coordinate(lat, lon));
        _lat = lat;
        _lon = lon;
    }
}
