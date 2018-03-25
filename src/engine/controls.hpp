#ifndef BLAVENCIA_ENGINE_CONTROLS_HPP
#define BLAVENCIA_ENGINE_CONTROLS_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

namespace controls {

sf::Vector2f keyboard_directions();
float mouse_relative_angle ( const sf::Vector2f& object_position, const sf::RenderWindow& window );

template <sf::Mouse::Button T>
class mouse_button_edge {
public:
    static bool run()
    {
        bool edge = sf::Mouse::isButtonPressed ( T ) && !state_;
        state_ = sf::Mouse::isButtonPressed ( T );
        return edge;
    }
private:
    static bool state_;
};

template<sf::Mouse::Button T>
bool mouse_button_edge<T>::state_ = false;
}

#endif // BLAVENCIA_ENGINE_CONTROLS_HPP
