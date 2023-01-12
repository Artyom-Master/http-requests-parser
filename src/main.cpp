#include <iostream>

#include "HttpRequestsParser.h"

void printParsedHttpRequest(const std::unique_ptr<HttpRequestsParser>& httpQueriesParser)
{
    std::cout << "HTTP method of request: ";

    switch (httpQueriesParser->getHttpMethod())
    {
    case HttpMethods::get:
    {
        std::cout << "GET\n";
    }break;
    case HttpMethods::put:
    {
        std::cout << "PUT\n";
    }break;
    case HttpMethods::connect:
    {
        std::cout << "CONNECT\n";
    }break;
    case HttpMethods::head:
    {
        std::cout << "HEAD\n";
    }break;
    case HttpMethods::post:
    {
        std::cout << "POST\n";
    }break;
    case HttpMethods::unknown:
    {
        std::cout << "UNKNOWN\n";
    }break;
    }

    std::cout << "URL: " << httpQueriesParser->getUrl() << "\n";
    std::cout << "Host: " << httpQueriesParser->getValueOfHeader("Host") << "\n";
    std::cout << "User-Agent: " << httpQueriesParser->getValueOfHeader("User-Agent") << "\n";
    std::cout << "Accept: " << httpQueriesParser->getValueOfHeader("Accept") << "\n";
    std::cout << "Connection: " << httpQueriesParser->getValueOfHeader("Connection") << "\n";
    std::cout << "\n";
}

int main()
{
    std::unique_ptr<HttpRequestsParser> httpRequestsParser{
        std::make_unique<HttpRequestsParser>() };

    printParsedHttpRequest(httpRequestsParser);
    std::cout << "\n";

    const char* str{ "GET /wiki/http HTTP/1.1\r\n"
            "Host: ru.wikipedia.org\r\n"
            "User-Agent: Mozilla/5.0 "
            "(X11; U; Linux i686; ru; rv:1.9b5) "
            "Gecko/2008050509 Firefox/3.0b5\r\n"
            "Accept: text/html\r\n"
            "Connection: close\r\n" };
    
    {
        std::string httpRequest{ str };

        if (httpRequestsParser->parse(std::move(httpRequest)))
            printParsedHttpRequest(httpRequestsParser);

        std::cout << "Size of httpRequest after moving: " << httpRequest.size() << "\n";
    }

	return 0;
}