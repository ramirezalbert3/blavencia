#ifndef BLAVENCIA_ENGINE_CONTROLS_HPP
#define BLAVENCIA_ENGINE_CONTROLS_HPP

#include <SFML/Window.hpp>
#include <cmath>

namespace controls {

sf::Vector2f arrow_directions()
{
    sf::Vector2f direction {0,0};
    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Left ) ) {
        direction.x = -1;
    } else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Right ) ) {
        direction.x = 1;
    }

    if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Up ) ) {
        direction.y = -1;
    } else if ( sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Down ) ) {
        direction.y = 1;
    }
    return direction;
}

float mouse_relative_angle ( const sf::Vector2f& object_position )
{
    const sf::Vector2f mouse_rel_pos {
        sf::Mouse::getPosition().x - object_position.x,
        sf::Mouse::getPosition().y- object_position.y
    };
    const auto mouse_rel_pos_magnitude = std::sqrt ( mouse_rel_pos.x*mouse_rel_pos.x
                                         + mouse_rel_pos.y*mouse_rel_pos.y );

    float angle = 180.f/3.1416 * std::acos ( -mouse_rel_pos.y/mouse_rel_pos_magnitude );

    angle = ( mouse_rel_pos.x < 0 ) ? 360 - angle : angle;

    return angle;
}

}

#endif // BLAVENCIA_ENGINE_CONTROLS_HPP
