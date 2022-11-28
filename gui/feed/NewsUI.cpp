#include "NewsUI.h"

using namespace std;
using namespace Wt;

namespace
{
    const int PUBLISHER = 0;
    const int TITLE = 1;
    const int LINK = 2;
    const int IMG = 3;
    const int DATE = 4;
}

NewsUI::~NewsUI() {}

NewsUI::NewsUI() : WContainerWidget()
{
    setStyleClass("text-white newsfeed mt-4 content");

    NewsRequester *nr = new NewsRequester();
    Request r(nr->getHost(), nr->getHeaders(), nr);
    news = r.getData();

    if (news.size() > 0)
    {
        for (int i = 0; i < news.size(); i++)
        {
            if (news[i][IMG] != "null") {
                WContainerWidget *article = this->addWidget(make_unique<WContainerWidget>());
                buildFeedItem(article, i);
            }
        }
    } else {
        this->addWidget(make_unique<WText>("Too many News API calls: Limited to 100 per day."));
    }
}

void NewsUI::buildFeedItem(WContainerWidget *article, const int index)
{
    article->setStyleClass("newscolor d-flex flex-column");

    // Create an anchor that links to a URL through an image.
    WLink link = WLink(news[index][LINK]);
    link.setTarget(LinkTarget::NewWindow);
    WAnchor *anchor = article->addWidget(make_unique<WAnchor>(link));
    WImage *image = anchor->addNew<WImage>(WLink(news[index][IMG]));
    image->setStyleClass("img-fluid");

    WContainerWidget *publish = article->addWidget(make_unique<WContainerWidget>());
    publish->setStyleClass("d-flex flex-row px-2 text-left mt-4 mb-3");
    WText *site = publish->addWidget(make_unique<WText>(news[index][PUBLISHER]));
    site->setStyleClass("p-2");
    WText *date = publish->addWidget(make_unique<WText>(news[index][DATE]));
    date->setStyleClass("p-2 pl-2 low-font");

    WText *title = article->addWidget(make_unique<WText>(news[index][TITLE]));
    title->setStyleClass("px-3 mb-3 high-font");
}