#ifndef BLAVENCIA_COMPONENTS_CELL_HPP
#define BLAVENCIA_COMPONENTS_CELL_HPP

#include <memory>
#include <SFML/Graphics.hpp>

class cell_t {
public:
     template <typename T>
     cell_t ( const T& x ) : impl_ ( std::make_unique<T> ( x ) ) {}

     cell_t ( const cell_t& x ) : impl_ ( x.impl_->copy() ) {}

     struct cell_impl_t {
          virtual ~cell_impl_t() = default;
          virtual std::unique_ptr<cell_impl_t> copy() const = 0;
          sf::RectangleShape shape_;
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

private:
     std::unique_ptr<cell_impl_t> impl_;
};

#endif // BLAVENCIA_COMPONENTS_CELL_HPP
