#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

template<std::size_t R, std::size_t C>
class map_t {
public:
     map_t ( estd::matrix<cell_t, R, C> map ) : cells ( map ) {}
     map_t ( std::initializer_list<std::initializer_list<cell_t>> map ) : cells ( estd::matrix<cell_t, R, C> {map} ) {}

     map_t ( const map_t& x ) = default;
     map_t ( map_t&& ) noexcept = default;
     map_t& operator= ( const map_t& x ) = default;
     map_t& operator= ( map_t&& ) = default;

private:
     estd::matrix<cell_t, R, C> cells;
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
