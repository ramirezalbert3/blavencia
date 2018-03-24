#ifndef BLAVENCIA_COMPONENTS_CHARACTER_HPP
#define BLAVENCIA_COMPONENTS_CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "utils/keyboard.hpp"

constexpr float character_size_ratio = 0.9;

class character_t {
public:
    character_t ( const sf::Vector2f& cell_size ) :
        shape_ ( cell_size * character_size_ratio ),
        speed_ ( cell_size / 10.f )
    {
        shape_.setPosition ( cell_size );
        shape_.setFillColor ( sf::Color::Red );
    }

    auto try_to_move() const
    {
        auto movement = sf::Vector2f {keyboard::move_with_arrows().x * speed_.x,
                                      keyboard::move_with_arrows().y * speed_.y
                                     };
        auto movement_trial = shape_;
        movement_trial.move ( movement );

        return movement_trial;
    }

    auto move ( const sf::Vector2f& movement )
    {
        return shape_.move ( movement );
    }

    auto draw ( sf::RenderWindow& target )
    {
        return target.draw ( shape_ );
    }

    auto getPosition() const
    {
        return shape_.getPosition();
    }

    auto getGlobalBounds() const
    {
        return shape_.getGlobalBounds();
    }

    auto speed() const
    {
        return speed_;
    }

private:
    sf::Vector2f speed_ {2, 2};
    sf::RectangleShape shape_;
};

#endif // BLAVENCIA_COMPONENTS_CHARACTER_HPP


