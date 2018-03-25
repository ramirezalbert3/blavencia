#include <SFML/Graphics.hpp>

#include "components/map.hpp"
#include "components/character.hpp"

#include "engine/collision.hpp"

#include "utils/csv.hpp"
#include "utils/surroundings.hpp"

int main()
{
    map_t map {csv::parse ( "map1.csv" ), {800, 600}};
    character_t player {{ map.cell_width(), map.cell_height() }};

    sf::RenderWindow world ( sf::VideoMode ( map.width(), map.height() ), "Blavencia" );
    world.setFramerateLimit ( 60 );

    while ( world.isOpen() ) {
        sf::Event event;
        while ( world.pollEvent ( event ) ) {
            if ( event.type == sf::Event::Closed )
                world.close();
        }

        auto final_position = player.try_to_move();

        collision::limit_movement ( player.getPosition(),
                                    final_position,
                                    player.speed(),
                                    map );

        const auto movement = final_position.getPosition() - player.getPosition();
        player.move ( movement );

        auto surrounding_cells = surroundings::surrounding_cells ( player.getGlobalBounds(), map ) ;

        world.clear ( sf::Color::Black );
        map.draw ( world );
        player.draw ( world );
        world.display();
    }

    return 0;
}


