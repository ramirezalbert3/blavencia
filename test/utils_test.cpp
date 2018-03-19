#include "gtest/gtest.h"
#include <utils/matrix.hpp>
#include <iostream>

TEST ( MatrixTest, Basic )
{
    estd::matrix<double, 3, 3> m {
        {1, 2, 3},
        {4, 6, 7},
        {7, 8, 11}
    };

//     for(auto &row : m)
//     {
//         for(auto &col : row)
//         {
//             std::cout << col << " ";
//         }
//         std::cout << "\n";
//     }
//     EXPECT_TRUE(false);
}
