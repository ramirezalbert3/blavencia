#include <SFML/Graphics.hpp>
#include <components/map.hpp>

int main()
{
    sf::RenderWindow world(sf::VideoMode(500, 500), "Blavencia");
    world.setFramerateLimit(60);
    
    cell_t empty{cell_t::empty{}};
    cell_t wall{cell_t::empty{}};
    
    estd::matrix<cell_t, 3, 3> cells   {{wall, wall,  wall},
                                        {wall, empty, wall},
                                        {wall, wall,  wall}
                                        };
                                        
//     map_t<3, 3> map(cells);
    
//     map_t<3, 3> map {   {wall, wall,  wall},
//                         {wall, empty, wall},
//                         {wall, wall,  wall}
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
