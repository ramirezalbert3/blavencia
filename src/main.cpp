#include <SFML/Graphics.hpp>
#include "components/map.hpp"
#include "components/character.hpp"
#include "utils/csv.hpp"
#include "utils/collision.hpp"

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

        auto movement_trial = player.try_to_move();

        auto movement = collision::limit_movement ( player.getPosition(),
                              movement_trial,
                              map );

//         auto final_position = movement_trial.getPosition();

        player.move ( movement);

        world.clear ( sf::Color::Black );
        map.draw ( world );
        player.draw ( world );
        world.display();
    }

    return 0;
}

