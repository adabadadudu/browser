#include "tel-renderer.hpp"
#include <utils/log.hpp>

void TelescopeRenderer::render(std::string code, TelescopeParser parser)
{
    objects = parser.parse_star(code);

    sf::Font jetbrains_mono;
    jetbrains_mono.loadFromFile("JetBrainsMono/fonts/ttf/JetBrainsMono-Regular.ttf");

    int voff = 0;
    for (auto object : objects)
    {
        object.text += "\n\n";
        sf::Text text(object.text, jetbrains_mono, object.size);

        text.setPosition(0, voff);

        text.setFillColor(sf::Color(object.color));

	text.setStyle(object.style);
	
        texts.push_back(text);

        voff += object.size * 2;
    }

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "AWB (Telescope)");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::Resized:
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                break;
            }

            default:
                break;
            }

            window.clear(sf::Color(0x282c34ff));

            for (auto &text : texts)
            {
                window.draw(text);
            }
        }
        window.display();
    }
}
