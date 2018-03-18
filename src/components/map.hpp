#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include "utils/matrix.hpp"
#include "components/cell.hpp"

template<std::size_t R, std::size_t C>
class map_t {
public:
     map_t ( estd::matrix<cell_t, R, C> map ) : cells ( map ) {}
private:
     estd::matrix<cell_t, R, C> cells;
};

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
