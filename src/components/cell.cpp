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

sf::Vector2f cell_t::getPosition() const
{
    return impl_->shape_.getPosition();
}

std::experimental::optional<sf::FloatRect> cell_t::bounding_rectangle() const
{
    return impl_->bounding_rectangle();
}

void cell_t::setTexture ( const textures::texture_map& map )
{
    impl_->setTexture ( map );
}

// cell_t::empty::
void cell_t::empty::setTexture ( const textures::texture_map& map )
{
    shape_.setTexture ( &map.at ( "empty" ) );
}
std::unique_ptr<cell_t::cell_impl_t> cell_t::empty::copy() const
{
    return std::make_unique<empty> ( *this );
};
std::experimental::optional<sf::FloatRect> cell_t::empty::bounding_rectangle() const
{
    return std::experimental::nullopt;
}

// cell_t::wall::
void cell_t::wall::setTexture ( const textures::texture_map& map )
{
    shape_.setTexture ( &map.at ( "wall" ) );
}
std::unique_ptr<cell_t::cell_impl_t> cell_t::wall::copy() const
{
    return std::make_unique<wall> ( *this );
};
std::experimental::optional<sf::FloatRect> cell_t::wall::bounding_rectangle() const
{
    return std::experimental::optional<sf::FloatRect> {shape_.getGlobalBounds() };
}
