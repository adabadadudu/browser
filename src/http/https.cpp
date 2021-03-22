#include "https.hpp"

extern "C"
{
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
}

#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <vector>

void Https::connect(std::string url, int port)
{

    const char *name_c = url.c_str();

    struct hostent host = *gethostbyname(name_c);

    struct sockaddr_in address;

    address.sin_family = AF_INET;

    address.sin_port = htons(port); // Port 443 (https)

    bcopy((char *)host.h_addr, (char *)&address.sin_addr.s_addr, host.h_length);

    Https::socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (Https::socket_ == -1)
    {
        std::cerr << "socket creation failure\n";
    }

    if (::connect(Https::socket_, (const struct sockaddr *)&address, sizeof(address)) != 0)
    {
        std::cerr << "Connection failure\n";
    }

    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = TLS_client_method();

    SSL_CTX *ctx = SSL_CTX_new(method);

    ssl = SSL_new(ctx);

    if (!ssl)
    {
        std::cerr << "Error creating SSL.\n";
        return;
    }

    SSL_set_fd(ssl, socket_);

    int err = SSL_connect(ssl);
    if (err <= 0)
    {
        std::cout << "Error creating SSL connection.  err=" << err;
    }
}

std::string Https::make_request(std::string request) // Function to send a packet then receive one
{
    constexpr auto BUFFER_SIZE = 10000;

    SSL_write(ssl, request.c_str(), request.length());

    sleep(1);

    std::vector<char> buffer(BUFFER_SIZE);
    int len;

    do
    {
        len = SSL_read(ssl, buffer.data(), 100);

        std::cout << buffer.data();

    } while (len > 0);

    std::cout << buffer.data();

    return buffer.data();
}

std::string Https::drop_headers(std::string document)
{
    int location = document.find("\r\n\r\n");

    std::string pure = document.substr(location + 4);

    return pure;
}

std::string Https::entry_point(std::string url, int port)
{
    connect(url, port);

    std::string request = "GET /index.html HTTP/1.1\nHost: " + url + "\n\n";

    std::string response = make_request(request);

    response = drop_headers(response);

    return response;
}
