#include <SFML/Graphics.hpp>
#include <components/map.hpp>

int main()
{
     sf::RenderWindow world ( sf::VideoMode ( 500, 500 ), "Blavencia" );
     world.setFramerateLimit ( 60 );

     map_t<3, 3> map {  {cell_t::wall{}, cell_t::wall{},  cell_t::wall{}},
                        {cell_t::wall{}, cell_t::empty{}, cell_t::wall{}},
                        {cell_t::wall{}, cell_t::wall{},  cell_t::wall{}}};

     while ( world.isOpen() ) {
          sf::Event event;
          while ( world.pollEvent ( event ) ) {
               if ( event.type == sf::Event::Closed )
                    world.close();
          }

          world.clear ( sf::Color::Black );
          world.display();
     }

     return 0;
}
