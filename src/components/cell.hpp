#ifndef BLAVENCIA_COMPONENTS_CELL_HPP
#define BLAVENCIA_COMPONENTS_CELL_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class cell_t {
public:
    struct cell_impl_t {
        virtual ~cell_impl_t() = default;
        virtual std::unique_ptr<cell_impl_t> copy() const = 0;
        sf::RectangleShape shape_ {sf::Vector2f{5, 5}};
    };

    struct empty : public cell_impl_t {
        empty()
        {
            shape_.setFillColor ( sf::Color::Black );
        }
        std::unique_ptr<cell_impl_t> copy() const override
        {
            return std::make_unique<empty> ( *this );
        };
    };

    struct wall : public cell_impl_t {
        wall()
        {
            shape_.setFillColor ( sf::Color::Green );
        }
        std::unique_ptr<cell_impl_t> copy() const override
        {
            return std::make_unique<wall> ( *this );
        };
    };

    cell_t() : impl_ ( std::make_unique<empty> ( empty {} ) ) {}

    cell_t ( std::unique_ptr<cell_impl_t>&& x ) : impl_ ( std::move ( x ) ) {}

    cell_t ( empty x ) : impl_ ( std::make_unique<empty> ( x ) ) {}
    cell_t ( wall x ) : impl_ ( std::make_unique<wall> ( x ) ) {}

    cell_t ( const std::string& name );

    cell_t ( const cell_t& x ) : impl_ ( x.impl_->copy() ) {}
    cell_t ( cell_t&& ) noexcept = default;

    cell_t& operator= ( const cell_t& x )
    {
        return *this = cell_t ( x );
    }
    cell_t& operator= ( cell_t&& ) = default;

    void setPosition ( float x, float y );
    void setSize (float width, float height);
    void draw ( sf::RenderWindow& target ) const;

private:
    std::unique_ptr<cell_impl_t> impl_;
};

#endif // BLAVENCIA_COMPONENTS_CELL_HPP
