#ifndef BLAVENCIA_ENGINE_KEYBOARD_HPP
#define BLAVENCIA_ENGINE_KEYBOARD_HPP

#include <SFML/Graphics.hpp>

namespace keyboard {

sf::Vector2f move_with_arrows()
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

}

#endif // BLAVENCIA_ENGINE_KEYBOARD_HPP
