#include "gtest/gtest.h"
#include <utils/matrix.hpp>
#include <utils/csv.hpp>
#include <iostream>

TEST ( matrix_test, basic )
{
    estd::matrix<double> m {
        {1, 2, 3},
        {4, 6, 7},
        {7, 8, 11}
    };

    for ( auto &row : m ) {
        for ( auto &col : row ) {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
//     EXPECT_TRUE(false);
}

TEST ( csv_parser, basic )
{
    auto result = csv::parse ( "test.csv" );

    for ( auto &row : result ) {
        for ( auto &col : row ) {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
//     EXPECT_TRUE(false);
}

TEST ( csv_parser, fail_to_open_and_throw )
{
    EXPECT_THROW ( csv::parse ( "non_existant.csv" ), std::runtime_error );
}
