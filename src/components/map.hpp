#ifndef BLAVENCIA_COMPONENTS_MAP_HPP
#define BLAVENCIA_COMPONENTS_MAP_HPP

#include <array>
#include <cassert>

namespace estd
{
    template<class T, std::size_t R, std::size_t C>
    using matrix = T[R][C];
//     struct matrix
//     {
//         T data[R][C];
//     };
}

#endif // BLAVENCIA_COMPONENTS_MAP_HPP
