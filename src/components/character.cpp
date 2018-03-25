#include "components/character.hpp"
#include "engine/controls.hpp"

constexpr float character_size_ratio = 0.7;

character_t::character_t ( const sf::Vector2f& cell_size ) :
    shape_ ( cell_size * character_size_ratio ),
    speed_ ( cell_size / 10.f )
{
    const auto recangle = shape_.getGlobalBounds();
    const sf::Vector2f midpoint {
        recangle.left + recangle.width/2,
                      recangle.top + recangle.height/2
    };
    shape_.setOrigin ( midpoint );

    shape_.setPosition ( cell_size * 2.f );
    shape_.setFillColor ( sf::Color::Red );
}

sf::RectangleShape character_t::try_to_move() const
{
    auto movement = sf::Vector2f {controls::keyboard_directions().x * speed_.x,
                                  controls::keyboard_directions().y * speed_.y
                                 };
    auto movement_trial = shape_;
    movement_trial.move ( movement );

    return movement_trial;
}

void character_t::move ( const sf::Vector2f& movement, const sf::RenderWindow& window )
{
    shape_.move ( movement );
    auto angle = controls::mouse_relative_angle ( shape_.getPosition(), window );
    shape_.setRotation ( angle );
}

void character_t::draw ( sf::RenderWindow& target )
{
    target.draw ( shape_ );
}

sf::Vector2f character_t::getPosition() const
{
    return shape_.getPosition();
}

sf::FloatRect character_t::getGlobalBounds() const
{
    return shape_.getGlobalBounds();
}

sf::Vector2f character_t::speed() const
{
    return speed_;
}

float character_t::angle() const
{
    return shape_.getRotation();
}
