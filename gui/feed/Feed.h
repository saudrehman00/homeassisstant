#ifndef FEED_H
#define FEED_H

#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WFont.h>
#include <vector>

class Feed {
    public:
        virtual void buildFeedItem(Wt::WContainerWidget *item) = 0;
};

#endif