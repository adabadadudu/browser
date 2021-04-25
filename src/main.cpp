#include <engine/orca.hpp>
#include <http/http.hpp>
#include <http/https.hpp>
#include <iostream>
#include <parsing/parser.hpp>
#include <render/renderer.hpp>
#include <utils/log.hpp>

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

    log(DEBUG, "%s", css["p"]["color"].c_str());
    
    orca::Engine engine(parser.root_node, css);

    Renderer renderer(css);

    renderer.render(engine.to_layout_data());

    renderer.main();
    return 0;
}
