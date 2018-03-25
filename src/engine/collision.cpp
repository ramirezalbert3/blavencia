#include "engine/collision.hpp"
#include <SFML/Graphics.hpp>
#include "components/map.hpp"

std::vector<const cell_t*> collision::surrounding_cells (
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

sf::RectangleShape collision::move_out_collision_shortest_distance ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const sf::FloatRect& intersection )
{
    // this is necessary to avoid getting stuck when sliding from one wall-cell to another
    const auto speed_with_margin = movement_speed * 1.5f;
    if ( intersection.width <= speed_with_margin.x && intersection.height <= speed_with_margin.y )
        return tried_location;

    sf::Vector2f correction = {0, 0};

    const sf::Vector2f midpoint {
        tried_location.getGlobalBounds().left + tried_location.getGlobalBounds().width/2,
                                       tried_location.getGlobalBounds().top + tried_location.getGlobalBounds().height/2
    };
    const bool move_left = ( intersection.left > midpoint.x );
    const bool move_up = ( intersection.top > midpoint.y );

    if ( intersection.width < intersection.height ) {
        correction = {intersection.width, 0};
        correction = move_left ? -correction : correction;
    } else if ( intersection.width > intersection.height ) {
        correction = {0, intersection.height};
        correction = move_up ? -correction : correction;
    } else {
        correction += move_up ?
                      sf::Vector2f {0, -intersection.height} :
                      sf::Vector2f {0, intersection.height};
        correction += move_left ?
                      sf::Vector2f {-intersection.width, 0} :
                      sf::Vector2f {intersection.width, 0};
    }

    auto final_location = tried_location;
    final_location.move ( correction );

    return final_location;
}

sf::RectangleShape collision::limit_with_edges ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& current_position,
        const sf::Vector2f& map_size )
{
    auto final_location = tried_location;

    const auto rectangle = tried_location.getGlobalBounds();
    const auto min_x = rectangle.left;
    const auto max_x = rectangle.left + rectangle.width;
    const auto min_y = rectangle.top;
    const auto max_y = rectangle.top + rectangle.height;

    if ( min_x < 0 || max_x > map_size.x )
        final_location.setPosition ( { current_position.x, final_location.getPosition().y} );
    if ( min_y < 0 || max_y > map_size.y )
        final_location.setPosition ( { final_location.getPosition().x, current_position.y} );

    return final_location;
}

sf::RectangleShape collision::limit_with_collisions ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const map_t& map )
{
    auto final_location = tried_location;
    unsigned intersections_count = 0;
    for ( const auto & row : map ) {
        for ( const auto & cell : row ) {
            if ( auto cell_bounds = cell.bounding_rectangle() ) {
                sf::FloatRect intersection;
                if ( final_location.getGlobalBounds().intersects ( cell_bounds.value(),  intersection ) ) {
                    intersections_count++;
                    final_location = move_out_collision_shortest_distance ( final_location,
                                     movement_speed, intersection );
                }
            }
        }
    }

    if ( intersections_count > 3 ) throw std::runtime_error ( "Found more than 3 intersections!" );

    return final_location;
}

sf::Vector2f collision::limit_movement ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& current_position,
        const sf::Vector2f& movement_speed,
        const map_t& map )
{
    if ( tried_location.getPosition() == current_position ) return {0, 0};

    // auto surrounding_cells = surrounding_cells ( player.getGlobalBounds(), map ) ;
    auto final_location = collision::limit_with_collisions ( tried_location,
                          movement_speed,
                          map );

    final_location = collision::limit_with_edges ( final_location,
                     current_position, {map.width(), map.height() } );

    return ( final_location.getPosition() - current_position );
}
