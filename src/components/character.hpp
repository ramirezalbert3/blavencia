#ifndef BLAVENCIA_COMPONENTS_CHARACTER_HPP
#define BLAVENCIA_COMPONENTS_CHARACTER_HPP

#include <SFML/Graphics.hpp>


class character_t {
public:
    character_t ( const sf::Vector2f& cell_size );

    sf::RectangleShape try_to_move() const;
    void move ( const sf::Vector2f& movement );

    void draw ( sf::RenderWindow& target );

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    sf::Vector2f speed() const;

private:
    sf::RectangleShape shape_;
    sf::Vector2f speed_ {2, 2};
};

#endif // BLAVENCIA_COMPONENTS_CHARACTER_HPP
