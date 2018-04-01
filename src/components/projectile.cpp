#include <cmath>

#include "components/projectile.hpp"
#include "components/map.hpp"
#include "engine/controls.hpp"

constexpr float degs_to_rads = 3.141592/180;
projectile_t::projectile_t ( const sf::Vector2f& cell_size, const sf::Vector2f& initial_position, float angle ) :
    shape_ ( {cell_size.x * 0.2f, cell_size.y * 0.3f} ), speed_ ( cell_size / 6.f ),
       direction_ ( {std::sin ( angle * degs_to_rads ), -std::cos ( angle * degs_to_rads ) } )
{   // TODO: bug with direction (projectiles do not end up where the mouse points), likely origin issue
    const auto recangle = shape_.getGlobalBounds();
    const sf::Vector2f midpoint {
        recangle.left + recangle.width/2,
                      recangle.top + recangle.height/2
    };
    shape_.setOrigin ( midpoint );

    shape_.setPosition ( initial_position );
    shape_.setRotation ( angle );
    shape_.setFillColor ( sf::Color::Black );
}

controls::mouse_button_edge<sf::Mouse::Button::Left> left_button_edge;

std::experimental::optional<projectile_t> projectile_t::create_projetile (
    const sf::Vector2f& cell_size, const sf::Vector2f& initial_position, float angle
)
{
    if ( !left_button_edge.run() ) return std::experimental::nullopt;
    return projectile_t {cell_size, initial_position, angle};
}

void projectile_t::move ()
{
    auto movement = sf::Vector2f {direction_.x * speed_.x,
                                  direction_.y * speed_.y
                                 };
    shape_.move ( movement );
}

void projectile_t::draw ( sf::RenderWindow& target )
{
    target.draw ( shape_ );
}

sf::Vector2f projectile_t::getPosition() const
{
    return shape_.getPosition();
}

sf::FloatRect projectile_t::getGlobalBounds() const
{
    return shape_.getGlobalBounds();
}
