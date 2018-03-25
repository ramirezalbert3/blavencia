#ifndef BLAVENCIA_UTILS_MATRIX_HPP
#define BLAVENCIA_UTILS_MATRIX_HPP

#include <initializer_list>
#include <vector>
#include <stdexcept>
#include <string>

namespace estd {
template<class T>
struct matrix {

    matrix ( const matrix& x ) = default;
    matrix ( matrix&& ) noexcept = default;
    matrix& operator= ( const matrix& x ) = default;
    matrix& operator= ( matrix&& ) = default;
    matrix() = default;

    matrix ( std::initializer_list<std::initializer_list<T>> list )
    {
        data.reserve ( list.size() );

        const auto columns = list.begin()->size();

        for ( auto l : list ) {
            if ( columns != l.size() ) {
                const std::string msg = "Not all columns are equal in size found " +
                                        std::to_string ( columns ) + " and " +
                                        std::to_string ( l.size() );
                throw std::out_of_range ( msg );
            }
            data.push_back ( std::vector<T> ( l ) );
        }
    }

    matrix ( const std::vector<std::vector<T>>& x ) : data ( x ) {}

    template <typename other>
    matrix ( matrix<other> x ) : data (
            [x]()
    {
        std::vector<std::vector<T>> result;
        result.reserve ( x.size() );
        for ( auto element : x ) {
            result.push_back ( std::vector<T> {element.begin(), element.end() } );
        }
        return result;
    } ()
    ) {}

    auto reserve ( std::size_t size )
    {
        return data.reserve ( size );
    }
    auto push_back ( std::vector<T> element )
    {
        return data.push_back ( element );
    }
    auto size () const
    {
        return data.size();
    }
    auto begin()
    {
        return data.begin();
    }
    auto begin() const
    {
        return data.begin();
    }
    auto end()
    {
        return data.end();
    }
    auto end() const
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

    bool operator== ( const matrix &m )
    {
        if ( m.size() != size() ) return false;
        auto own = begin();
        for ( auto& other : m ) {
            if ( other.size() != own->size() ) return false;
            if ( !std::equal ( own->begin(), own->end(), other.begin() ) ) return false;
            own++;
        }
        return true;
    }

    bool operator!= ( const matrix &m )
    {
        return ! ( *this == m );
    }
private:
    std::vector<std::vector<T>> data;
};
}

#endif // BLAVENCIA_UTILS_MATRIX_HPP
