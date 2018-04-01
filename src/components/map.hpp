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
    bool is_cell_empty ( const sf::Vector2f& point ) const;
    std::vector<const cell_t*> surrounding_cells ( const sf::Vector2f& point ) const;

private:
    auto find_cell ( const sf::Vector2f& point ) const
    {
        auto is_in_this_row = [&point, this] ( const std::vector<cell_t>& row ) {
            return ( point.y >= row[0].getPosition().y &&
                     point.y < row[0].getPosition().y + cell_height() );
        };

        auto is_in_this_col = [&point] ( const cell_t& col ) {
            return ( point.x >= col.getPosition().x &&
                     point.x < col.getPosition().x + col.size().x );
        };

        auto row = std::find_if ( begin(), end(), is_in_this_row );
        auto col = std::find_if ( row->begin(), row->end(), is_in_this_col );
        return std::tie ( row, col );
    }
    estd::matrix<cell_t> cells;
    sf::Vector2f map_size_ = {};
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
