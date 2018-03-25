#include "components/map.hpp"

map_t::map_t ( estd::matrix<cell_t> map,
               sf::Vector2f map_size,
               const textures::texture_map& textures )
    : cells ( map ), map_size_ ( map_size )
{
    const auto cell_width = map_size.x / map.columns();
    const auto cell_height = map_size.y / map.rows();
    std::size_t y = 0;
    for ( auto &row : cells ) {
        std::size_t x = 0;
        for ( auto &cell : row ) {
            cell.setSize ( cell_width, cell_height );
            cell.setPosition ( x * cell_width, y * cell_height );
            cell.setTexture ( textures );
            x++;
        }
        y++;
    }
}

float map_t::width() const
{
    return map_size_.x;
}

float map_t::height() const
{
    return map_size_.y;
}

float map_t::cell_width() const
{
    return map_size_.x / cells.columns();
}

float map_t::cell_height() const
{
    return map_size_.y / cells.rows();
}

void map_t::draw ( sf::RenderWindow& target )
{
    for ( const auto &cells_row : cells ) {
        for ( const auto &cell : cells_row ) {
            cell.draw ( target );
        }
    }
}
