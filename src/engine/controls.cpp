#include "engine/controls.hpp"

sf::Vector2f controls::keyboard_directions()
{
    sf::Vector2f direction {0,0};
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::A ) ) {
        direction.x = -1;
    } else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::D ) ) {
        direction.x = 1;
    }

    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::W ) ) {
        direction.y = -1;
    } else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::S ) ) {
        direction.y = 1;
    }
    return direction;
}

float controls::mouse_relative_angle ( const sf::Vector2f& object_position, const sf::RenderWindow& window )
{
    const sf::Vector2f mouse_rel_pos {
        sf::Mouse::getPosition ( window ).x - object_position.x,
        sf::Mouse::getPosition ( window ).y - object_position.y
    };
    const auto mouse_rel_pos_magnitude = std::sqrt ( mouse_rel_pos.x*mouse_rel_pos.x
                                         + mouse_rel_pos.y*mouse_rel_pos.y );

    float angle = 180.f/3.1416 * std::acos ( -mouse_rel_pos.y/mouse_rel_pos_magnitude );

    angle = ( mouse_rel_pos.x < 0 ) ? 360 - angle : angle;

    return angle;
}
