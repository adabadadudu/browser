#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SFML/Graphics.hpp>
#include <engine/data.hpp>
#include <parsing/dom.hpp>
#include <parsing/parser.hpp>

class Renderer
{
public:
    Renderer(std::map<std::string, std::map<std::string, std::string>> p_css);
    void render(std::vector<orca::LayoutData> layout_data);
    void main();
    std::map<std::string, std::map<std::string, std::string>> css;

private:
    sf::Font font;
    std::vector<sf::Text> texts;
    orca::LayoutData ld;
};
#endif
