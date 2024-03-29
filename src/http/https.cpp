#include "https.hpp"

extern "C"
{
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
}
#include <strings.h>
#include <unistd.h>
#include <utils/log.hpp>
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
        log(ERROR, "socket creation failure");
    }

    if (::connect(Https::socket_, (const struct sockaddr *)&address, sizeof(address)) != 0)
    {
        log(ERROR, "Connection failure\n");
    }

    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = TLS_client_method();

    SSL_CTX *ctx = SSL_CTX_new(method);

    ssl = SSL_new(ctx);

    if (!ssl)
    {
        log(ERROR, "Error creating SSL.");
        return;
    }

    SSL_set_fd(ssl, socket_);

    int err = SSL_connect(ssl);
    if (err <= 0)
    {
        log(ERROR, "Error creating SSL connection.  err=%d", err);
    }
}

std::string Https::make_request(std::string request) // Function to send a packet then receive one
{
    constexpr auto BUFFER_SIZE = 10000;

    SSL_write(ssl, request.c_str(), request.length());

    ssize_t r = -1;

    usleep(2000);

    std::vector<char> buffer(BUFFER_SIZE);

    do
    {
        r = SSL_read(ssl, buffer.data(), BUFFER_SIZE);

        if (r == 0)
        {
            log(WARNING, "Reached the end of data stream.");
            continue;
        }

        printf("%s", buffer.data());

    } while (r < 0);

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

    std::string request = "GET /index.html HTTP/1.1\r\nHost: " + url + "\r\n\r\n";

    std::string response = make_request(request);

    response = drop_headers(response);

    return response;
}
