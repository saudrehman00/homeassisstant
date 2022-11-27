#ifndef NEWSREQUESTER_H
#define NEWSREQUESTER_H

#include "Requester.h"

class Request;

class NewsRequester : public Requester {
    public:
        void getData(Request* request);
        NewsRequester();
        ~NewsRequester();
};

#endif