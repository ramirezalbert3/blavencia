#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

template<std::size_t R, std::size_t C>
class map_t {
public:
     map_t ( estd::matrix<cell_t, R, C> map ) : cells ( map )
     {
          set_cells_position();
     }
     map_t ( std::initializer_list<std::initializer_list<cell_t>> map ) : map_t ( estd::matrix<cell_t, R, C> {map} ) {}

     map_t ( const map_t& x ) = default;
     map_t ( map_t&& ) noexcept = default;
     map_t& operator= ( const map_t& x ) = default;
     map_t& operator= ( map_t&& ) = default;

     constexpr auto height() const
     {
          return cell_size * R;
     }

     constexpr auto width() const
     {
          return  cell_size * C;
     }

     void draw ( sf::RenderWindow& target )
     {
          for ( auto &cells_row : cells ) {
               for ( auto &cell : cells_row ) {
                    cell.draw ( target );
               }
          }
     }

private:
     void set_cells_position()
     {
          std::size_t row = 0;
          std::size_t col = 0;
          for ( auto &cells_row : cells ) {
               for ( auto &cell : cells_row ) {
                    cell.setPosition ( row * cell_size, col * cell_size );
                    col++;
               }
               row++;
          }
     }
     estd::matrix<cell_t, R, C> cells;
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
