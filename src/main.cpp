#include <SFML/Graphics.hpp>
#include <components/map.hpp>

int main()
{
    sf::RenderWindow world(sf::VideoMode(500, 500), "Blavencia");
    world.setFramerateLimit(60);
    
//     using ct = cell_t::type;
//     
//     map_t<3, 3> map {   {ct::wall, ct::wall,  ct::wall},
//                         {ct::wall, ct::empty, ct::wall},
//                         {ct::wall, ct::door,  ct::wall}
//                         };

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
