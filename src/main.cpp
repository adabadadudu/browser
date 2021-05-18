#include <engine/orca.hpp>
#include <http/http.hpp>
#include <http/https.hpp>
#include <parsing/parser.hpp>
#include <render/renderer.hpp>
#include <telescope/tel-parser.hpp>
#include <telescope/tel-renderer.hpp>
#include <telescope/telescope.hpp>
#include <utils/log.hpp>
int main(int argc, char *argv[])
{

    std::string url = "127.0.0.1";
    int port = 8000;
    /*if (argc > 1)
        url = argv[1];
    if (argc >= 2)
        port = std::atoi(argv[2]);*/

    Http h;

    h.connect(url, port); // For web server testing

    std::string response = h.entry_point(url, port);

    printf("%s", response.c_str());

    Parser parser;

    auto root = parser.parse_html(response);
    auto css = parser.css;

    orca::Engine engine(parser.root_node, css);

    Renderer renderer(css);

    renderer.render(engine.to_layout_data());

    renderer.main(url + ":" + std::to_string(port));
    if (argc > 1 && strcmp(argv[1], "--telescope") == 0)
    {
        Telescope telescope;
        telescope.connect("127.0.0.1");
        std::string response = telescope.make_request();
        TelescopeParser tel_parser;
        std::vector<TelescopeObject> objects = tel_parser.parse_star("* Hello!\n** Hello2\n*** Hello3\n");

        TelescopeRenderer renderer;

        renderer.render(response, tel_parser);
    }

    return 0;
}
