#ifndef _TELESCOPE_PARSER_HPP
#define _TELESCOPE_PARSER_HPP
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
struct TelescopeObject
{
    std::string text;
    int size = 16;
    uint32_t color = 0xFFFFFFFF, style = sf::Text::Regular;
};

class TelescopeParser
{
public:
    std::vector<TelescopeObject> parse_star(std::string code);
};

#endif
