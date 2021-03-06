#ifndef BLAVENCIA_ENGINE_COLLISION_HPP
#define BLAVENCIA_ENGINE_COLLISION_HPP

#include <vector>
#include <experimental/optional>

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

std::experimental::optional<sf::FloatRect> detect_collision ( const sf::FloatRect& object,
        const cell_t& cell );

sf::RectangleShape move_out_collision_shortest_distance ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const sf::FloatRect& intersection );

sf::RectangleShape limit_with_edges ( const sf::RectangleShape& tried_location,
                                      const sf::Vector2f& current_position,
                                      const sf::Vector2f& map_size );

sf::RectangleShape limit_with_collisions ( const sf::RectangleShape& tried_location,
        const sf::Vector2f& movement_speed,
        const std::vector<const cell_t*>& surrounding_cells );

sf::Vector2f limit_movement ( const sf::RectangleShape& tried_location,
                              const sf::Vector2f& current_position,
                              const sf::Vector2f& movement_speed,
                              const map_t& map );

}

#endif // BLAVENCIA_ENGINE_COLLISION_HPP
