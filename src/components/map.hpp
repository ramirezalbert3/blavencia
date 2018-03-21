#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

class map_t {
public:
    map_t ( estd::matrix<cell_t> map ) : cells ( map )
    {
        std::size_t y = 0;
        for ( auto &row : cells ) {
            std::size_t x = 0;
            for ( auto &cell : row ) {
                cell.setPosition ( x * cell_size, y * cell_size );
                x++;
            }
            y++;
        }
    }
    map_t ( std::initializer_list<std::initializer_list<cell_t>> map ) : map_t ( estd::matrix<cell_t> {map} ) {}
//     map_t ( estd::matrix<std::string> map ) : map_t ( estd::matrix<cell_t> {map} ) {}

    map_t ( const map_t& x ) = default;
    map_t ( map_t&& ) noexcept = default;
    map_t& operator= ( const map_t& x ) = default;
    map_t& operator= ( map_t&& ) = default;

    constexpr auto height() const
    {
        return cell_size * cells.rows();
    }

    constexpr auto width() const
    {
        return cell_size * cells.columns();
    }

    void draw ( sf::RenderWindow& target )
    {
        for ( const auto &cells_row : cells ) {
            for ( const auto &cell : cells_row ) {
                cell.draw ( target );
            }
        }
    }

private:
    estd::matrix<cell_t> cells;
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
