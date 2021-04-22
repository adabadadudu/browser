#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SFML/Graphics.hpp>
#include <parsing/dom.hpp>
#include <parsing/parser.hpp>
class Renderer
{
public:
    Renderer(DOMNode *root, std::map<std::string, std::map<std::string, std::string>> p_css);
    void render_node(DOMNode *n);
    void main();
    std::map<std::string, std::map<std::string, std::string>> css;

private:
    sf::Font font;
    sf::Text text;
    LayoutData ld;
};
#endif
