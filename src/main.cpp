#include <SFML/Graphics.hpp>
#include <components/map.hpp>

int main()
{
    map_t<5, 5> map {
        {cell_t::wall{}, cell_t::wall{},  cell_t::wall{}, cell_t::wall{},  cell_t::wall{}},
        {cell_t::wall{}, cell_t::empty{}, cell_t::wall{}, cell_t::empty{},  cell_t::wall{}},
        {cell_t::wall{}, cell_t::empty{},  cell_t::wall{}, cell_t::empty{},  cell_t::wall{}},
        {cell_t::wall{}, cell_t::empty{}, cell_t::empty{}, cell_t::empty{},  cell_t::wall{}},
        {cell_t::wall{}, cell_t::wall{},  cell_t::wall{}, cell_t::wall{},  cell_t::wall{}}
    };

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
