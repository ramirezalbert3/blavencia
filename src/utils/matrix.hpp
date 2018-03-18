#ifndef BLAVENCIA_UTILS_MATRIX_HPP
#define BLAVENCIA_UTILS_MATRIX_HPP

#include <initializer_list>
#include <array>
#include <exception>

namespace estd {
template<class T, std::size_t R, std::size_t C>
struct matrix {
     matrix ( std::initializer_list<std::initializer_list<T>> list )
     {
          if ( list.size() != R ) {
               std::string msg = "Matrix has " + std::to_string ( R ) + " rows and initializer list has " + std::to_string ( list.size() );
               throw std::out_of_range ( msg );
          }

          std::size_t row = 0;
          for ( auto l : list ) {
               if ( l.size() != C ) {
                    std::string msg = "Matrix has " + std::to_string ( C ) + " columns and initializer list has " + std::to_string ( l.size() );
                    throw std::out_of_range ( msg );
               }
               std::copy ( l.begin(), l.end(), data[row].begin() );
               row++;
               if ( row >= C ) break;
          }
     }

     matrix ( const matrix& x ) = default;
     matrix ( matrix&& ) noexcept = default;
     matrix& operator= ( const matrix& x ) = default;
     matrix& operator= ( matrix&& ) = default;
     matrix() = default;

     auto begin()
     {
          return data.begin();
     }
     auto end()
     {
          return data.end();
     }

     std::array<std::array<T, C>, R> data;
};
}

#endif // BLAVENCIA_UTILS_MATRIX_HPP
