#include "NewsRequest.h"

using namespace std;
using namespace curlpp::options;

NewsRequest::~NewsRequest() {}

NewsRequest::NewsRequest(string host) : host(host) {}


void NewsRequest::execute() {
    
}

void NewsRequest::cleanData() {
}

