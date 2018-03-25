#ifndef BLAVENCIA_COMPONENTS_CELL_HPP
#define BLAVENCIA_COMPONENTS_CELL_HPP

#include <memory>
#include <string>
#include <experimental/optional>
#include <SFML/Graphics.hpp>

#include "engine/textures.hpp"

class cell_t {
public:
    struct cell_impl_t {
        virtual ~cell_impl_t() = default;
        virtual std::unique_ptr<cell_impl_t> copy() const = 0;
        virtual std::experimental::optional<sf::FloatRect> bounding_rectangle() const = 0;
        virtual void setTexture ( const textures::texture_map& map ) = 0;
        sf::RectangleShape shape_ {sf::Vector2f{5, 5}};
    };

    struct empty : public cell_impl_t {
        empty()
        {
//             shape_.setFillColor ( sf::Color::Black );
        }
        void setTexture(const textures::texture_map& map) override
        {
            shape_.setTexture(&map.at("empty"));
        }
        std::unique_ptr<cell_impl_t> copy() const override
        {
            return std::make_unique<empty> ( *this );
        };
        std::experimental::optional<sf::FloatRect> bounding_rectangle() const override
        {
            return std::experimental::nullopt;
        }
    };

    struct wall : public cell_impl_t {
        wall()
        {
//             shape_.setFillColor ( sf::Color::Green );
        }
        void setTexture(const textures::texture_map& map) override
        {
            shape_.setTexture(&map.at("wall"));
        }
        std::unique_ptr<cell_impl_t> copy() const override
        {
            return std::make_unique<wall> ( *this );
        };
        std::experimental::optional<sf::FloatRect> bounding_rectangle() const override
        {
            return std::experimental::optional<sf::FloatRect> {shape_.getGlobalBounds() };
        }
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
    void setSize ( float width, float height );
    sf::Vector2f size() const;
    sf::Vector2f getPosition() const;
    std::experimental::optional<sf::FloatRect> bounding_rectangle() const;
    void draw ( sf::RenderWindow& target ) const;
    void setTexture(const textures::texture_map& map)
    {
        impl_->setTexture(map);
    }

#ifdef __debug__
    void paint()
    {
        impl_->shape_.setFillColor ( sf::Color::Blue );
    }
#endif // __debug__

private:
    std::unique_ptr<cell_impl_t> impl_;
};

#endif // BLAVENCIA_COMPONENTS_CELL_HPP
