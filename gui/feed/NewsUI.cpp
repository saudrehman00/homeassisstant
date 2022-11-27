#include "NewsUI.h"

using namespace std;
using namespace Wt;

NewsUI::~NewsUI() {}

NewsUI::NewsUI() : WContainerWidget() {
    setHeight(550);
    setStyleClass("text-white mt-4 d-flex bg-light flex-row justify-content-center");

    for (int i = 0; i < 7; i++) {
        WContainerWidget *article = this->addWidget(make_unique<WContainerWidget>());
        article->setStyleClass("text-left mx-4 d-flex flex-column justify-content-between");
        buildFeedItem(article);
        articles.push_back(article);
    }
}

void NewsUI::buildFeedItem(WContainerWidget *article) {
    WText *publisher = article->addWidget(make_unique<WText>("JOURNAL"));
    
    // Create an anchor that links to a URL through an image.
    WLink link = WLink("https://www.emweb.be/");
    link.setTarget(LinkTarget::NewWindow);
    unique_ptr<WAnchor> anchor = make_unique<WAnchor>(link);
    anchor->addNew<WImage>(WLink("https://www.emweb.be/css/emweb_small.png"));

    WText *title = article->addWidget(make_unique<WText>("ARTICLE"));
    title->setStyleClass("px-3 high-font");
    WText *date = article->addWidget(make_unique<WText>("DATE"));
    date->setStyleClass("low-font");

    WText *condition = article->addWidget(make_unique<WText>("SUNNY"));
}