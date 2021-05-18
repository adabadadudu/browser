#ifndef TELESCOPE_H
#define TELESCOPE_H
#include <string>

class Telescope
{
public:
    int socket_;

    void connect(std::string url,int port = 5742);
    std::string make_request();
};

#endif
