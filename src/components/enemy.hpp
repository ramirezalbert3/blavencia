#ifndef BLAVENCIA_COMPONENTS_ENEMY_HPP
#define BLAVENCIA_COMPONENTS_ENEMY_HPP

#include <chrono>
#include <SFML/Graphics.hpp>

class map_t;
class enemy_t {
public:
    enemy_t ( const sf::Vector2f& cell_size );

    void move ( const map_t& map );

    void draw ( sf::RenderWindow& target );

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    sf::Vector2f speed() const;
    float angle() const;

private:
    void set_facing_direction ( const sf::Vector2f &movement );

    bool handle_standing();

    sf::RectangleShape shape_ {};
    sf::Vector2f speed_ {1, 1};

    struct probability_t {
        double change_of_direction = 0.05;
        double stand_still = 0.02;
    } probability;

    sf::Vector2f movement_ {0, 0};
    std::chrono::time_point<std::chrono::system_clock> standing_timestamp_ {};

    // TODO(aramirez): std::variant <moving, standing> state_;
};

#endif // BLAVENCIA_COMPONENTS_ENEMY_HPP

