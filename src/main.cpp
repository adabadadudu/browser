#include <http/http.hpp>
#include <http/https.hpp>
#include <iostream>
#include <layout/engine.hpp>
#include <parsing/parser.hpp>
#include <render/renderer.hpp>
int main(int argc, char *argv[])
{

    std::string url = "127.0.0.1";
    if (argc > 1)
        url = argv[1];

    Http h;

    h.connect(url, 8000); // For web server testing

    std::string response = h.entry_point(url, 8000);

    std::cout << response;

    Parser parser;

    auto root = parser.parse_html(response);
    auto css = parser.css;

    std::cout << root->children[1]->children[0]->children[1]->children[0]->children[0]->attributes["class"] << std::endl;

    Renderer renderer(parser.root_node, css);

    renderer.render_node(root->children[1]->children[0]->children[1]->children[0]->children[0], 0);
    renderer.render_node(root->children[1]->children[0]->children[0], 30);
    
    renderer.main();
    return 0;
}
