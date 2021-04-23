#include "renderer.hpp"
#include <iostream>
Renderer::Renderer(std::map<std::string, std::map<std::string, std::string>> p_css)
    : css(p_css)
{
}
void Renderer::main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "AWB");

    font.loadFromFile("assets/times-new-roman.ttf");

    for (auto &text : texts)
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

        for (auto &text : texts)
            window.draw(text);

        window.display();
    }
}

void Renderer::render_node(DOMNode *n)
{

    sf::Text text;

    text.setCharacterSize(std::atoi(css[n->attributes["class"]]["font-size"].c_str()));

    std::cout << "text: " << n->text << std::endl;

    auto color = sf::Color {n->layout_data.color};

    text.setFillColor(color);

    text.setString(n->text);

    texts.push_back(text);
}
