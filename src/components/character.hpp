#ifndef BLAVENCIA_COMPONENTS_CHARACTER_HPP
#define BLAVENCIA_COMPONENTS_CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "utils/keyboard.hpp"

class character_t {
public:
    character_t ( const sf::Vector2f& cell_size ) : shape_ ( cell_size * 0.98f )
    {
        shape_.setPosition ( cell_size );
        shape_.setFillColor ( sf::Color::Red );
    }

    void update ( )
    {
        sf::Vector2f movement = {keyboard::move_with_arrows().x * speed_.x,
                                 keyboard::move_with_arrows().y * speed_.y
                                };
        shape_.move ( movement );
    }

    void draw ( sf::RenderWindow& target )
    {
        target.draw ( shape_ );
    }

    sf::Vector2f getPosition() const
    {
        return shape_.getPosition();
    }

private:
    sf::Vector2f speed_ {2, 2};
    sf::RectangleShape shape_;
};

#endif // BLAVENCIA_COMPONENTS_CHARACTER_HPP


