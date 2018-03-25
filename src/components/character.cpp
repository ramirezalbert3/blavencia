#include "components/character.hpp"
#include "engine/keyboard.hpp"

constexpr float character_size_ratio = 0.9;

character_t::character_t ( const sf::Vector2f& cell_size ) :
    shape_ ( cell_size * character_size_ratio ),
    speed_ ( cell_size / 10.f )
{
    shape_.setPosition ( cell_size );
    shape_.setFillColor ( sf::Color::Red );
}

sf::RectangleShape character_t::try_to_move() const
{
    auto movement = sf::Vector2f {keyboard::move_with_arrows().x * speed_.x,
                                  keyboard::move_with_arrows().y * speed_.y
                                 };
    auto movement_trial = shape_;
    movement_trial.move ( movement );

    return movement_trial;
}

void character_t::move ( const sf::Vector2f& movement )
{
    shape_.move ( movement );
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
