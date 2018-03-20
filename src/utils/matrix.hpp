#ifndef BLAVENCIA_UTILS_MATRIX_HPP
#define BLAVENCIA_UTILS_MATRIX_HPP

#include <initializer_list>
#include <vector>
#include <exception>
#include <string>

namespace estd {
template<class T>
struct matrix {
    matrix ( std::initializer_list<std::initializer_list<T>> list )
    {
        data.reserve ( list.size() );

        const auto columns = list.begin()->size();

        for ( const auto& l : list ) {
            if ( columns != l.size() ) {
                const std::string msg = "Not all columns are equal in size found " +
                                        std::to_string ( columns ) + " and " +
                                        std::to_string ( l.size() );
                throw std::out_of_range ( msg );
            }
            data.push_back ( std::vector<T> ( l ) );
        }
    }

    matrix ( const std::string& filepath );

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
    auto rows() const
    {
        return data.size();
    }
    auto columns() const
    {
        return data.begin()->size();
    }
private:
    std::vector<std::vector<T>> data;
};
}

#endif // BLAVENCIA_UTILS_MATRIX_HPP
