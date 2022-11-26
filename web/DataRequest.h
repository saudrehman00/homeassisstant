#ifndef REQUEST_H
#define REQUEST_H

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

class DataRequest
{
public:
    virtual void execute() = 0;
    void requestData(std::string host);

protected:
    virtual void cleanData() = 0;
};

#endif
