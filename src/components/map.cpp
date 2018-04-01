#include <boost/range/iterator_range.hpp>
#include <type_traits>

#include "components/map.hpp"
#include <string>

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

std::vector<const cell_t*> map_t::surrounding_cells ( const sf::Vector2f& point ) const
{
    std::vector<const cell_t*> cells;
    cells.reserve ( 9 );

    const auto iter_pair = find_cell ( point );
    const auto row = std::get<0> ( iter_pair );
    const auto column = std::get<1> ( iter_pair );
    const auto column_offset = std::distance ( row->begin(), column );

    const auto range_begin = ( row == begin() ) ? begin() : row - 1;
    const auto range_end = ( row >= end()-1 ) ? end() : row + 2; // 1 past range end
    auto range = boost::iterator_range<decltype ( range_begin ) > ( range_begin, range_end );

    for ( auto & it : range ) {
        const auto col = it.begin() + column_offset;
        cells.push_back ( & ( *col ) );
        if ( col != it.begin() ) {
            cells.push_back ( & ( * ( col-1 ) ) );
        }
        if ( col <= it.end()-2 ) {
            cells.push_back ( & ( * ( col+1 ) ) );
        }
    }

    return cells;
}

std::vector<const cell_t*> map_t::surrounding_cells ( const sf::FloatRect& rectangle ) const
{
    const sf::Vector2f midpoint {
        rectangle.left + rectangle.width/2,
                       rectangle.top + rectangle.height/2
    };
    return surrounding_cells(midpoint);
}

bool map_t::is_cell_empty ( const sf::Vector2f& point ) const
{
    if ( point.x < 0 || point.x > width() ||
            point.y < 0 || point.y > height() ) {
        using namespace std::string_literals; // NOLINT
        throw std::runtime_error ( "Position ["s + std::to_string ( point.x ) + ", "s +  std::to_string ( point.y ) + "]" +
                                   "out of map ["s +  std::to_string ( width() ) + ", "s +  std::to_string ( height() ) + "]" );
    }

    const auto iter_pair = find_cell ( point );
    const auto cell = std::get<1> ( iter_pair );

    return cell->is_empty();
}


