#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow world(sf::VideoMode(500, 500), "Blavencia");
    world.setFramerateLimit(60);

    while (world.isOpen())
    {
        sf::Event event;
        while (world.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                world.close();
        }

        world.clear(sf::Color::Black);
        world.display();
    }

    return 0;
}
