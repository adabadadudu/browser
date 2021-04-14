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
    parser.parse_html("<body> <div> <p> Hello </p> </div> </body>");
    std::cout << "Text data of " << parser.root_node->children[0]->name << " is "
              << "'" << parser.root_node->children[0]->text << "'" <<std::endl;

    std::cout << "Found node: " << parser.find_node(parser.root_node, "div")->name << std::endl;
    return 0;
}
