#include "telescope.hpp"
extern "C"
{
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
}
#include <string>
#include <strings.h>
#include <unistd.h>
#include <utils/log.hpp>
#include <vector>

void Telescope::connect(std::string url, int port)
{
    const char *name_c = url.c_str();

    struct hostent host = *gethostbyname(name_c);

    struct sockaddr_in address;

    address.sin_family = AF_INET;

    address.sin_port = htons(port);

    bcopy((char *)host.h_addr, (char *)&address.sin_addr.s_addr, host.h_length);

    Telescope::socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (Telescope::socket_ == -1)
    {
        log(ERROR, "socket creation failure");
    }

    if (::connect(Telescope::socket_, (const struct sockaddr *)&address, sizeof(address)) != 0)
    {
        log(ERROR, "Connection failure");
    }

    log(INFO, "Connected to %s:%d via Telescope", name_c, port);
}

std::string Telescope::make_request()
{
    constexpr auto BUFFER_SIZE = 10000;

    std::string request = "/index.star 0";
    
    send(Telescope::socket_, request.c_str(), std::string(request).length(), 0);

    std::vector<char> buffer(BUFFER_SIZE);

    read(Telescope::socket_, buffer.data(), buffer.size());

    return buffer.data();
}
