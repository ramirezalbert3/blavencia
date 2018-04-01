#include <SFML/Graphics.hpp>

#include "components/map.hpp"
#include "components/character.hpp"
#include "components/projectile.hpp"

#include "engine/collision.hpp"
#include "engine/textures.hpp"

#include "utils/csv.hpp"

int main()
{
    const auto texture_map = textures::load_texture_map ( {{"empty", "grass"}, {"wall", "bricks"}} );
    const std::string dat_path = DBG_DAT_PATH;
    const std::string map_path = dat_path + std::string ( "/maps/map1.csv" );
    map_t map {csv::parse ( map_path ), {600, 600}, texture_map};
    const auto cell_size = sf::Vector2f {map.cell_width(), map.cell_height() };

    character_t player {cell_size};

    std::vector<projectile_t> projectiles;
    projectiles.reserve ( 128 );

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

        player.move ( movement, world );

        if ( auto projectile = projectile_t::create_projetile (
                                   cell_size,
                                   player.getPosition(),
                                   player.angle()
                               ) ) {
            projectiles.push_back ( projectile.value() );
        }

        update_projectiles ( projectiles, map );

#ifdef __debug__
        auto surrounding_cells = map.surrounding_cells ( player.getGlobalBounds() ) ;
        for ( auto& cell : surrounding_cells )
            const_cast<cell_t*> ( cell )->dbg_paint();
#endif // __debug__

        world.clear ( sf::Color::Black );
        map.draw ( world );
        player.draw ( world );
        std::for_each ( projectiles.begin(), projectiles.end(),
        [&world] ( projectile_t& p ) {
            p.draw ( world );
        } );
        world.display();
    }

    return 0;
}
