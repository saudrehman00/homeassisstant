#include "NewsUI.h"

using namespace std;
using namespace Wt;

NewsUI::~NewsUI() {}

NewsUI::NewsUI() : WContainerWidget() {
    setHeight(550);
    setStyleClass("text-white d-flex bg-light flex-row justify-content-center");

    for (int i = 0; i < 7; i++) {
        WContainerWidget *article = this->addWidget(make_unique<WContainerWidget>());
        article->setStyleClass("text-left mx-4 d-flex flex-column justify-content-between");
        buildFeedItem(article);
        articles.push_back(article);
    }
}

void NewsUI::buildFeedItem(WContainerWidget *article) {
    WText *date = article->addWidget(make_unique<WText>("TODAY"));

    WContainerWidget *temperature = article->addWidget(make_unique<WContainerWidget>());
    temperature->setStyleClass("text-left d-flex flex-row");
    
    WImage *image = temperature->addWidget(make_unique<WImage>(WLink("../images/weather/sun.png")));
    image->setWidth(50);
    image->setHeight(50);

    WText *high = temperature->addWidget(make_unique<WText>("MX°"));
    high->setStyleClass("px-3 high-font");
    WText *low = temperature->addWidget(make_unique<WText>("MN°"));
    low->setStyleClass("low-font");

    WText *condition = article->addWidget(make_unique<WText>("SUNNY"));
}