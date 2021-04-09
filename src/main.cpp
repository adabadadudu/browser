#include "http/http.hpp"
#include "http/https.hpp"
#include "parsing/parser.hpp"
#include <iostream>
int main(int argc, char *argv[])
{

    std::string url = argv[1];
    Http h;

    h.connect(url, 8000); // For web server testing

    std::string response = h.entry_point(url, 8000);

    std::cout << response;

    Parser parser;
    parser.parse_html("<html> <div> <p>");
    return 0;
}
