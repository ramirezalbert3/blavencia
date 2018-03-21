#include <components/cell.hpp>

cell_t::cell_t ( const std::string& name ) : impl_ (
        [&name]() -> std::unique_ptr<cell_impl_t> {
    if ( name == "wall" ) return std::make_unique<wall> ( wall {} );
    return std::make_unique<empty> ( empty {} );
}() ) {}



void cell_t::setPosition ( float x, float y )
{
    impl_->shape_.setPosition ( x, y );
}

void cell_t::draw ( sf::RenderWindow& target ) const
{
    target.draw ( impl_->shape_ );
}