#include <components/cell.hpp>

cell_t::cell_t ( const std::string& name ) : impl_ (
        [&name]() -> std::unique_ptr<cell_impl_t> {
    if ( name == "wall" ) return std::make_unique<wall> ( wall {} );
    return std::make_unique<empty> ( empty {} );
}() ) {}

void cell_t::setPosition ( float x, float y )
{
    impl_->shape_.setPosition ( {x, y} );
}

void cell_t::setSize ( float width, float height )
{
    impl_->shape_.setSize ( {width, height} );
}

void cell_t::draw ( sf::RenderWindow& target ) const
{
    target.draw ( impl_->shape_ );
}

sf::Vector2f cell_t::size() const
{
    return impl_->shape_.getSize();
}

std::experimental::optional<sf::FloatRect> cell_t::bounding_rectangle() const
{
    return impl_->bounding_rectangle();
}
