#include "renderer.hpp"
#include <iostream>
Renderer::Renderer(DOMNode *root, std::map<std::string, std::map<std::string, std::string>> p_css)
{

    css = p_css;
}

void Renderer::main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "AWB");

    font.loadFromFile("assets/times-new-roman.ttf");

    text.setFont(font);

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}

void Renderer::render_node(DOMNode *n)
{

    text.setCharacterSize(std::atoi(css[n->attributes["class"]]["font-size"].c_str()));

    text.setFillColor(sf::Color::Black);

    text.setString(n->text);
}
