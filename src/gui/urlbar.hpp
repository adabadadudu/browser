#ifndef GUI_URL_BAR_HPP
#define GUI_URL_BAR_HPP
#include <SFML/Graphics.hpp>
#include <string>

class BottomBar
{
public:
    void make_bar(std::string url, sf::RenderWindow *win);
    sf::Text text;
    sf::RectangleShape rect;

private:
  sf::Font font;
};

#endif
