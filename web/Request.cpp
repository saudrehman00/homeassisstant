#include "Request.h"
#include "Requester.h"

using namespace std;

Request::Request(string host, Requester *requester) : _host(host), _requester(requester)
{
}

Request::Request(string host, list<string> headers, Requester *requester) : 
_host(host), _requester(requester), _headers(headers)
{
}


Request::~Request()
{
    delete this->_requester;
}

void Request::setRequester(Requester *requester)
{
    delete this->_requester;
    this->_requester = requester;
}

void Request::setHeaders(list<string> headers)
{
    this->_headers = headers;
}

void Request::setHost(string host)
{
    this->_host = host;
}

string Request::getHost()
{
    return _host;
}

list<std::string> Request::getHeaders()
{
    return _headers;
}

void Request::getData() {
    this->_requester->getData(this);
}