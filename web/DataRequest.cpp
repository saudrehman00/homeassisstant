#include "DataRequest.h"

void DataRequest::requestData(std::string host)
{
    try
    {
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;

        // Our request to be sent.
        curlpp::Easy myRequest;

        // Set the URL.
        curlpp::options::Url myUrl(host);
        // myRequest.setOpt<curlpp::options::Url>(hostname);
        myRequest.setOpt(myUrl);

        // Send request and get a result.
        // By default the result goes to standard output.
        myRequest.perform();
        std::cout << std::endl;
    }

    catch (curlpp::RuntimeError &e)
    {
        std::cout << e.what() << std::endl;
    }

    catch (curlpp::LogicError &e)
    {
        std::cout << e.what() << std::endl;
    }
}