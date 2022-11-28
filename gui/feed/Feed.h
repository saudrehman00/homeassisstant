#ifndef FEED_H
#define FEED_H

#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WFont.h>
#include <vector>
#include "../../data/location/LocationInfo.h"
#include "../../web/Request.h"

class Feed {
    public:
        virtual void buildFeedItem(Wt::WContainerWidget *item, const int index) = 0;
};

#endif