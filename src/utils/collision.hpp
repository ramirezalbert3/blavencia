#ifndef BLAVENCIA_UTILS_COLLISION_HPP
#define BLAVENCIA_UTILS_COLLISION_HPP

#include <SFML/Graphics.hpp>
#include "components/map.hpp"
#include <iostream>

namespace collision {

void move_out_collision_shortest_distance ( sf::RectangleShape& final_position,
        const sf::Vector2f& movement_speed,
        const sf::FloatRect& intersection )
{
    // this is necessary to avoid getting stuck when sliding from one wall-cell to another
    const auto speed_with_margin = movement_speed * 1.5f;
    if ( intersection.width <= speed_with_margin.x && intersection.height <= speed_with_margin.y ) return;

    sf::Vector2f correction = {0, 0};

    const sf::Vector2f midpoint {
        final_position.getGlobalBounds().left + final_position.getGlobalBounds().width/2,
                                       final_position.getGlobalBounds().top + final_position.getGlobalBounds().height/2
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

    final_position.move ( correction );
}

void limit_movement ( const sf::Vector2f& current_position,
                      sf::RectangleShape& final_position,
                      const sf::Vector2f& movement_speed,
                      const map_t& map )
{
    if ( final_position.getPosition() == current_position ) return;

    unsigned intersections_count = 0;
    for ( const auto & row : map ) {
        for ( const auto & cell : row ) {
            if ( auto cell_bounds = cell.bounding_rectangle() ) {
                sf::FloatRect intersection;
                if ( final_position.getGlobalBounds().intersects ( cell_bounds.value(),  intersection ) ) {
                    intersections_count++;
                    move_out_collision_shortest_distance ( final_position, movement_speed, intersection );
                }
            }
        }
    }

    sf::Vector2f out_of_map_correction = final_position.getPosition();
    const auto min_x = final_position.getGlobalBounds().left;
    const auto max_x = final_position.getGlobalBounds().left + final_position.getGlobalBounds().width;
    const auto min_y = final_position.getGlobalBounds().top;
    const auto max_y = final_position.getGlobalBounds().top + final_position.getGlobalBounds().height;
    if ( min_x < 0 || max_x > map.width() ) out_of_map_correction.x = current_position.x;
    if ( min_y < 0 || max_y > map.height() ) out_of_map_correction.y = current_position.y;

    final_position.setPosition ( out_of_map_correction );

    if ( intersections_count > 3 ) throw std::runtime_error ( "Found more than 3 intersections!" );
}

}

#endif // BLAVENCIA_UTILS_COLLISION_HPP


