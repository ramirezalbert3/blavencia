#include <SFML/Graphics.hpp>

#include "components/map.hpp"
#include "components/character.hpp"

#include "engine/collision.hpp"

#include "utils/csv.hpp"

int main()
{
    map_t map {csv::parse ( "maps/map1.csv" ), {800, 600}};
    character_t player {{ map.cell_width(), map.cell_height() }};

    sf::RenderWindow world ( sf::VideoMode ( map.width(), map.height() ), "Blavencia" );
    world.setFramerateLimit ( 60 );

    while ( world.isOpen() ) {
        sf::Event event;
        while ( world.pollEvent ( event ) ) {
            if ( event.type == sf::Event::Closed )
                world.close();
        }

        const auto tried_location = player.try_to_move();

        const auto movement = collision::limit_movement ( tried_location,
                              player.getPosition(),
                              player.speed(),
                              map );

        player.move ( movement );

#ifdef __debug__
        auto surrounding_cells = collision::surrounding_cells ( player.getGlobalBounds(), map ) ;
        for ( auto& cell : surrounding_cells )
            const_cast<cell_t*> ( cell )->dbg_paint();
#endif // __debug__

        world.clear ( sf::Color::Black );
        map.draw ( world );
        player.draw ( world );
        world.display();
    }

    return 0;
}


