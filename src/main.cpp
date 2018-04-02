#include <SFML/Graphics.hpp>

#include "components/map.hpp"
#include "components/character.hpp"
#include "components/projectile.hpp"
#include "components/enemy.hpp"

#include "engine/collision.hpp"
#include "engine/textures.hpp"

#include "utils/csv.hpp"

int main()
{
    std::srand ( std::time ( nullptr ) );
    const auto texture_map = textures::load_texture_map ( {{"empty", "grass"}, {"wall", "bricks"}} );
    const std::string dat_path = DBG_DAT_PATH;
    const std::string map_path = dat_path + std::string ( "/maps/map1.csv" );
    map_t map {csv::parse ( map_path ), {600, 600}, texture_map};
    const auto cell_size = sf::Vector2f {map.cell_width(), map.cell_height() };

    character_t player {cell_size};
    std::vector<enemy_t> enemies {{cell_size}, {cell_size}, {cell_size}, {cell_size}, {cell_size}};

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

        create_projetiles ( projectiles,
                            cell_size, player.getPosition(), player.angle() );
        move_projectiles ( projectiles );
        clean_projectiles ( projectiles, map );

        std::for_each ( enemies.begin(), enemies.end(),
        [&world, &map] ( enemy_t& e ) {
            e.move ( map );
        } );

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
        std::for_each ( enemies.begin(), enemies.end(),
        [&world] ( enemy_t& e ) {
            e.draw ( world );
        } );
        world.display();
    }

    return 0;
}
