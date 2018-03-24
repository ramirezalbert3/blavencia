#ifndef BLAVENCIA_UTILS_COLLISION_HPP
#define BLAVENCIA_UTILS_COLLISION_HPP

#include <SFML/Graphics.hpp>
#include "components/map.hpp"
#include <iostream>

namespace collision {

sf::Vector2f limit_movement ( const sf::Vector2f& current_position,
                              const sf::RectangleShape& trial_position,
                              const map_t& map )
{
    const auto final_rectangle = trial_position.getGlobalBounds();
    auto movement = trial_position.getPosition() - current_position;

    unsigned intersections_count = 0;
    for ( const auto & row : map ) {
        for ( const auto & cell : row ) {
            if ( auto cell_bounds = cell.bounding_rectangle() ) {
                sf::FloatRect intersection;
                if ( final_rectangle.intersects ( cell_bounds.value(),  intersection ) ) {
                    intersections_count++;
                    std::cout << movement.x << ", " << movement.y << std::endl;
//                     movement += sf::Vector2f {intersection.height, intersection.width};
                    std::cout << intersection.width << ", " << intersection.height << std::endl;
                }
            }
        }
    }
    if ( intersections_count > 2 ) throw std::runtime_error ( "Found more than 2 intersections!" );
    return movement;
}

}

#endif // BLAVENCIA_UTILS_COLLISION_HPP

