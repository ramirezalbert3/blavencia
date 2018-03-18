#ifndef BLAVENCIA_UTILS_MATRIX_HPP
#define BLAVENCIA_UTILS_MATRIX_HPP

#include <initializer_list>

namespace estd
{
    template<class T, std::size_t R, std::size_t C>
    using matrix = T[R][C];
}

#endif // BLAVENCIA_UTILS_MATRIX_HPP

