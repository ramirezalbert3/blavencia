#include <cmath>
#include <cstdlib>

#include "components/enemy.hpp"
#include "components/map.hpp"
#include "engine/collision.hpp"

constexpr float enemy_size_ratio = 0.65;

enemy_t::enemy_t ( const sf::Vector2f& cell_size ) :
    shape_ ( cell_size * enemy_size_ratio ),
    speed_ ( cell_size / 14.f ),
    movement_ ( { ( std::rand() % 3 - 1 ) * speed_.x,
              ( std::rand() % 3 - 1 ) * speed_.y
} )
{
    const auto recangle = shape_.getGlobalBounds();
    const sf::Vector2f midpoint {
        recangle.left + recangle.width/2,
                      recangle.top + recangle.height/2
    };
    shape_.setOrigin ( midpoint );

    shape_.setPosition ( cell_size * 2.f );
    shape_.setFillColor ( sf::Color::Blue );
}

bool enemy_t::handle_standing()
{
    auto standing_timer = std::chrono::system_clock::now() - standing_timestamp_;
    if ( standing_timer.count() < 3 ) {
        return true;
    }
    if ( ( std::rand() % 100 ) / 100.0f < probability.stand_still ) {
        standing_timestamp_ = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

void enemy_t::move ( const map_t & map )
{
    if ( handle_standing() ) return;

    if ( ( std::rand() % 100 ) / 100.0f < probability.change_of_direction ) {
        movement_ = { ( std::rand() % 3 - 1 ) * speed_.x,
                      ( std::rand() % 3 - 1 ) * speed_.y
                    };
    }
    auto tried_location = shape_;
    tried_location.move ( movement_ );
    movement_ = collision::limit_movement ( tried_location,
                                            getPosition(),
                                            speed(),
                                            map );

    shape_.move ( movement_ );

    set_facing_direction ( movement_ );
}

void enemy_t::set_facing_direction ( const sf::Vector2f &movement )
{
    const bool going_right = ( movement.x > 0 );
    const bool going_down = ( movement.y > 0 );
    const bool moving_vertically = ( std::abs ( movement.y ) > std::abs ( movement.x ) );
    auto angle = 0.0;
    if ( moving_vertically ) {
        angle = going_down ? 180 : 0;
    } else {
        angle = going_right ? 90 : 270;
    }
    shape_.setRotation ( angle );
}


// UTILS
void enemy_t::draw ( sf::RenderWindow& target )
{
    target.draw ( shape_ );
}

sf::Vector2f enemy_t::getPosition() const
{
    return shape_.getPosition();
}

sf::FloatRect enemy_t::getGlobalBounds() const
{
    return shape_.getGlobalBounds();
}

sf::Vector2f enemy_t::speed() const
{
    return speed_;
}

float enemy_t::angle() const
{
    return shape_.getRotation();
}


