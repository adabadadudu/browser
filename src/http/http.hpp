#ifndef HTTP_H
#define HTTP_H
#include <string>

class Http
{
public:
    int socket_;

    void connect(std::string url,int port = 80);
    std::string make_request(std::string request);
    std::string drop_headers(std::string document);
    std::string entry_point(std::string url, int port = 80);
};

#endif
