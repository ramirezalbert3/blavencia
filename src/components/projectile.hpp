#ifndef BLAVENCIA_COMPONENTS_PROJECTILE_HPP
#define BLAVENCIA_COMPONENTS_PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <experimental/optional>

class projectile_t {
public:
    projectile_t ( const sf::Vector2f& cell_size, const sf::Vector2f& initial_position, float angle );

    static std::experimental::optional<projectile_t> create_projetile (
        const sf::Vector2f& cell_size, const sf::Vector2f& initial_position, float angle
    );

    void move ();
    void draw ( sf::RenderWindow& target );

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape shape_;
    sf::Vector2f speed_ {2, 2};
    sf::Vector2f direction_ {1, 0};
};

class map_t;
void create_projetiles ( std::vector<projectile_t> &projectiles,
                         const sf::Vector2f& cell_size,
                         const sf::Vector2f& initial_position, float angle );
void clean_projectiles ( std::vector<projectile_t> &projectiles, const map_t& map );
void move_projectiles ( std::vector<projectile_t> &projectiles );

#endif // BLAVENCIA_COMPONENTS_PROJECTILE_HPP
