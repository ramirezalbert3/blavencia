#ifndef BLAVENCIA_UTILS_SURROUNDINGS_HPP
#define BLAVENCIA_UTILS_SURROUNDINGS_HPP

#include <algorithm>
#include <SFML/Graphics.hpp>
#include "components/map.hpp"

namespace surroundings {

std::vector<const cell_t*> surrounding_cells (
    const sf::FloatRect& object,
    const map_t& map )
{
    std::vector<const cell_t*> cells;
    cells.reserve ( 9 );

    const sf::Vector2f midpoint {
        object.left + object.width/2,
                    object.top + object.height/2
    };

    auto is_in_this_row = [&midpoint, &map] ( const std::vector<cell_t>& row ) {
        return ( midpoint.y >= row[0].getPosition().y &&
                 midpoint.y < row[0].getPosition().y + map.cell_height() );
    };

    auto is_in_this_col = [&midpoint] ( const cell_t& col ) {
        return ( midpoint.x >= col.getPosition().x &&
                 midpoint.x < col.getPosition().x + col.size().x );
    };

    const auto row = std::find_if ( map.begin(), map.end(), is_in_this_row );

    const auto range_begin = ( row == map.begin() ) ? map.begin() : row - 1;
    const auto range_end = ( row >= map.end()-1 ) ? map.end()-1 : row + 1;

    for ( auto it = range_begin; it<=range_end; ++it ) {
        const auto col = std::find_if ( it->begin(), it->end(), is_in_this_col );
        cells.push_back ( & ( *col ) );
        if ( col != it->begin() ) {
            cells.push_back ( & ( * ( col-1 ) ) );
        }
        if ( col >= it->end()-1 ) {
            cells.push_back ( & ( * ( col+1 ) ) );
        }
    }

    return cells;
}

}

#endif // BLAVENCIA_UTILS_SURROUNDINGS_HPP







