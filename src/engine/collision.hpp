#ifndef BLAVENCIA_UTILS_COLLISION_HPP
#define BLAVENCIA_UTILS_COLLISION_HPP

#include <vector>

namespace sf {
class RectangleShape;

template <class T>
class Vector2;
using Vector2f = Vector2<float>;

template <class T>
class Rect;
using FloatRect = Rect<float>;
}

class map_t;
class cell_t;

namespace collision {

std::vector<const cell_t*> surrounding_cells ( const sf::FloatRect& object,
        const map_t& map );

sf::RectangleShape move_out_collision_shortest_distance ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const sf::FloatRect& intersection );

sf::RectangleShape limit_with_edges ( const sf::RectangleShape& tried_location,
                                      const sf::Vector2f& current_position,
                                      const sf::Vector2f& map_size );

sf::RectangleShape limit_with_collisions ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const map_t& map );

sf::Vector2f limit_movement ( const sf::RectangleShape& tried_location,
                              const sf::Vector2f& current_position,
                              const sf::Vector2f& movement_speed,
                              const map_t& map );

}

#endif // BLAVENCIA_UTILS_COLLISION_HPP
