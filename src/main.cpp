#include "http/http.hpp"
#include "http/https.hpp"
#include <iostream>
int main(int argc, char *argv[])
{

    std::string url = argv[1];
    Http h;

    h.connect(url,8000); // For web server testing

    std::string response = h.entry_point(url,8000);

    std::cout << response;

    return 0;
}
