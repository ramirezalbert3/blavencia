#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

class map_t {
public:
    map_t ( estd::matrix<cell_t> map,
            sf::Vector2f map_size ) : cells ( map ), map_size_ ( map_size )
    {
        const auto cell_width = map_size.x / map.columns();
        const auto cell_height = map_size.y / map.rows();
        std::size_t y = 0;
        for ( auto &row : cells ) {
            std::size_t x = 0;
            for ( auto &cell : row ) {
                cell.setSize ( cell_width, cell_height );
                cell.setPosition ( x * cell_width, y * cell_height );
                x++;
            }
            y++;
        }
    }

    map_t ( std::initializer_list<std::initializer_list<cell_t>> map,
            sf::Vector2f map_size ) : map_t ( estd::matrix<cell_t> {map}, map_size ) {}

    map_t ( estd::matrix<std::string> map,
            sf::Vector2f map_size ) : map_t ( estd::matrix<cell_t> {map}, map_size ) {}

    map_t ( const map_t& x ) = default;
    map_t ( map_t&& ) noexcept = default;
    map_t& operator= ( const map_t& x ) = default;
    map_t& operator= ( map_t&& ) = default;

    auto width() const
    {
        return map_size_.x;
    }

    auto height() const
    {
        return map_size_.y;
    }

    auto cell_width() const
    {
        return map_size_.x / cells.columns();
    }

    auto cell_height() const
    {
        return map_size_.y / cells.rows();
    }
    auto begin() const
    {
        return cells.begin();
    }
    auto end() const
    {
        return cells.end();
    }

    void draw ( sf::RenderWindow& target )
    {
        for ( const auto &cells_row : cells ) {
            for ( const auto &cell : cells_row ) {
                cell.draw ( target );
            }
        }
    }

private:
    estd::matrix<cell_t> cells;
    sf::Vector2f map_size_ = {};
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
