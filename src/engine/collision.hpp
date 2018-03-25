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

void move_out_collision_shortest_distance ( sf::RectangleShape& final_position,
        const sf::Vector2f& movement_speed,
        const sf::FloatRect& intersection );

void limit_movement ( const sf::Vector2f& current_position,
                      sf::RectangleShape& final_position,
                      const sf::Vector2f& movement_speed,
                      const map_t& map );

}

#endif // BLAVENCIA_UTILS_COLLISION_HPP

