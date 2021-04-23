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

void Renderer::render(std::vector<orca::LayoutData> layout_data)
{

    for (auto div : layout_data)
    {
        sf::Text text;

        text.setCharacterSize(div.text_size);

        auto color = sf::Color{div.color};

        text.setFillColor(color);

        text.setString(div.text + '\n');

        texts.push_back(text);
    }
}
