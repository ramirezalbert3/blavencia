#include <boost/range/iterator_range.hpp>
#include <SFML/Graphics.hpp>

#include "engine/collision.hpp"
#include "components/map.hpp"

std::vector<const cell_t*> collision::surrounding_cells ( const sf::FloatRect& object,
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

    const auto begin = ( row == map.begin() ) ? map.begin() : row - 1;
    const auto end = ( row >= map.end()-1 ) ? map.end() : row + 2; // 1 past range end
    auto range = boost::iterator_range<decltype ( begin ) > ( begin, end );

    for ( auto & it : range ) {
        const auto col = std::find_if ( it.begin(), it.end(), is_in_this_col );
        cells.push_back ( & ( *col ) );
        if ( col != it.begin() ) {
            cells.push_back ( & ( * ( col-1 ) ) );
        }
        if ( col <= it.end()-2 ) {
            cells.push_back ( & ( * ( col+1 ) ) );
        }
    }

    return cells;
}

std::experimental::optional<sf::FloatRect> collision::detect_collision (
    const sf::FloatRect& object, const cell_t& cell )
{
    auto cell_bounds = cell.bounding_rectangle();
    if ( !cell_bounds ) return std::experimental::nullopt;

    sf::FloatRect intersection;

    auto collision_detected = object.intersects ( cell_bounds.value(),  intersection );
    if ( !collision_detected ) return std::experimental::nullopt;

    return intersection;
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
        const std::vector<const cell_t*>& surrounding_cells )
{
    auto final_location = tried_location;
    unsigned intersections_count = 0;

    for ( const auto cell : surrounding_cells ) {
        if ( auto intersection = detect_collision ( final_location.getGlobalBounds(), *cell ) ) {
            intersections_count++;
            final_location = move_out_collision_shortest_distance ( final_location,
                             movement_speed, intersection.value() );
        }
    }

    if ( intersections_count > 4 ) { // 4 intersections are possible when angled against a corner!
        const std::string msg = "Found " + std::to_string ( intersections_count ) + " intersections!";
        throw std::runtime_error ( msg );
    }

    return final_location;
}

sf::Vector2f collision::limit_movement ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& current_position,
        const sf::Vector2f& movement_speed,
        const map_t& map )
{
    if ( tried_location.getPosition() == current_position ) return {0, 0};

    const auto surrounding_cells = collision::surrounding_cells ( tried_location.getGlobalBounds(), map ) ;
    auto final_location = collision::limit_with_collisions ( tried_location,
                          movement_speed,
                          surrounding_cells );

    final_location = collision::limit_with_edges ( final_location,
                     current_position, {map.width(), map.height() } );

    return ( final_location.getPosition() - current_position );
}
