#ifndef NEWSREQUEST_H
#define NEWSREQUEST_H

#include "DataRequest.h"

class NewsRequest : public DataRequest {
    private:
        std::string host;
        void cleanData();

    public:
        NewsRequest(std::string host);
        ~NewsRequest();
        void execute();
};

#endif