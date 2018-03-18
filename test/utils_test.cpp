#include "gtest/gtest.h"
#include <utils/matrix.hpp>

TEST(MatrixTest, Basic) {
    estd::matrix<double, 3, 3> m {{
    {1, 2, 3},
    {4, 6},
    {7}
    }};
}
