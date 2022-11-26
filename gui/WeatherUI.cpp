#include "WeatherUI.h"

using namespace std;
using namespace Wt;

WeatherUI::WeatherUI() : WTemplate{tr("weather")} {
    addFunction("tr", &WTemplate::Functions::tr);
    
    WLabel *l = bindWidget("label", make_unique<WLabel>("here"));
    l->setText("here");
}

WeatherUI::~WeatherUI() {}