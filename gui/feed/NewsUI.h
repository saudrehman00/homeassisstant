#ifndef NEWSUI_H
#define NEWSUI_H

#include "Feed.h"
#include <Wt/WAnchor.h>

class NewsUI : public Wt::WContainerWidget, public Feed {
    private:
        std::vector<Wt::WContainerWidget *> articles;
        void buildFeedItem(Wt::WContainerWidget *article);

    public:
        NewsUI();
        ~NewsUI();

};

#endif