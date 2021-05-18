#ifndef _TELESCOPE_RENDERER_HPP
#define _TELESCOPE_RENDERER_HPP
#include <SFML/Graphics.hpp>
#include <telescope/tel-parser.hpp>

class TelescopeRenderer
{
public:
    void render(std::string code, TelescopeParser parser);

private:
    std::vector<TelescopeObject> objects;
    std::vector<sf::Text> texts;

   
};
#endif
