#ifndef BLAVENCIA_UTILS_COLLISION_HPP
#define BLAVENCIA_UTILS_COLLISION_HPP

#include <SFML/Graphics.hpp>
#include "components/map.hpp"

namespace collision {

void move_out_collision_shortest_distance ( const sf::Vector2f& current_position,
        sf::RectangleShape& final_position,
        const sf::FloatRect& intersection )
{
    // TODO: clean-up ignoring small collisions
    //       (avoids getting stuck when sliding between cells)
    if ( intersection.width < 5 && intersection.height < 5 ) return;
    sf::Vector2f correction = {0, 0};

    const auto movement = final_position.getPosition() - current_position;
    const bool moving_left = ( movement.x < 0 );
    const bool moving_up = ( movement.y < 0 );

    if ( intersection.width < intersection.height ) {
        correction = {intersection.width, 0};
        correction = moving_left ? correction : -correction;
    } else if ( intersection.width > intersection.height ) {
        correction = {0, intersection.height};
        correction = moving_up ? correction : -correction;
    } else {
        correction += moving_up ?
                      sf::Vector2f {0, intersection.height} :
                      sf::Vector2f {0, -intersection.height};
        correction += moving_left ?
                      sf::Vector2f {intersection.width, 0} :
                      sf::Vector2f {-intersection.width, 0};
    }

    final_position.move ( correction );
}

void limit_movement ( const sf::Vector2f& current_position,
                      sf::RectangleShape& final_position,
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
                    move_out_collision_shortest_distance ( current_position, final_position, intersection );
                }
            }
        }
    }
    if ( intersections_count > 3 ) throw std::runtime_error ( "Found more than 3 intersections!" );
}

}

#endif // BLAVENCIA_UTILS_COLLISION_HPP

