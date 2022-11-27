#include "NewsUI.h"

using namespace std;
using namespace Wt;

NewsUI::~NewsUI() {}

NewsUI::NewsUI() : WContainerWidget() {
    setStyleClass("text-white newsfeed mt-4 content");

    for (int i = 0; i < 8; i++) {
        buildFeedItem(this->addWidget(make_unique<WContainerWidget>()));
    }
}

void NewsUI::buildFeedItem(WContainerWidget *newsFeed) {
    newsFeed->setStyleClass("newscolor");

    // Create an anchor that links to a URL through an image.
    WLink link = WLink("https://www.emweb.be/");
    link.setTarget(LinkTarget::NewWindow);
    WAnchor *anchor = newsFeed->addWidget(make_unique<WAnchor>(link));
    WImage * image = anchor->addNew<WImage>(WLink("https://www.emweb.be/css/emweb_small.png"));    
    image->setMinimumSize(100, 100);

    WContainerWidget *publish = newsFeed->addWidget(make_unique<WContainerWidget>());
    publish->setStyleClass("d-flex flex-row px-2 text-left mt-4 mb-3");
    WText *site = publish->addWidget(make_unique<WText>("JOURNAL"));
    site->setStyleClass("p-2");
    WText *date = publish->addWidget(make_unique<WText>("DATE"));
    date->setStyleClass("p-2 pl-2 low-font");

    WText *title = newsFeed->addWidget(make_unique<WText>("ARTICLE"));
    title->setStyleClass("px-3 mb-3 high-font");
}