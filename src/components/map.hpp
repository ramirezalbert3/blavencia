#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

class map_t {
public:
    map_t ( estd::matrix<cell_t> map,
            sf::Vector2f map_size,
            const textures::texture_map& textures );

    map_t ( std::initializer_list<std::initializer_list<cell_t>> map,
            sf::Vector2f map_size,
            const textures::texture_map& textures ) : map_t ( estd::matrix<cell_t> {map}, map_size, textures ) {}

    map_t ( estd::matrix<std::string> map,
            sf::Vector2f map_size,
            const textures::texture_map& textures ) : map_t ( estd::matrix<cell_t> {map}, map_size, textures ) {}

    map_t ( const map_t& x ) = default;
    map_t ( map_t&& ) noexcept = default;
    map_t& operator= ( const map_t& x ) = default;
    map_t& operator= ( map_t&& ) = default;

    float width() const;
    float height() const;
    float cell_width() const;
    float cell_height() const;
    auto begin() const
    {
        return cells.begin();
    }
    auto end() const
    {
        return cells.end();
    }

    void draw ( sf::RenderWindow& target );

private:
    estd::matrix<cell_t> cells;
    sf::Vector2f map_size_ = {};
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
