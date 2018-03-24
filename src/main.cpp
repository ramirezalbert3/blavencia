#include <SFML/Graphics.hpp>
#include "components/map.hpp"
#include "utils/csv.hpp"

int main()
{
    map_t map {csv::parse ( "map1.csv" ), {800, 600}};

    sf::RenderWindow world ( sf::VideoMode ( map.width(), map.height() ), "Blavencia" );
    world.setFramerateLimit ( 60 );

    while ( world.isOpen() ) {
        sf::Event event;
        while ( world.pollEvent ( event ) ) {
            if ( event.type == sf::Event::Closed )
                world.close();
        }

        world.clear ( sf::Color::Black );
        map.draw ( world );
        world.display();
    }

    return 0;
}
