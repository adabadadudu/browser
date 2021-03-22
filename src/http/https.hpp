#ifndef HTTPS_H
#define HTTPS_H
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <string>

class Https
{
public:
    SSL *ssl;
    int socket_;

    void connect(std::string url, int port = 443);
    std::string make_request(std::string request);
    std::string drop_headers(std::string document);
    std::string entry_point(std::string url, int port = 443);
};

#endif
