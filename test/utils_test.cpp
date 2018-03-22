
#include <cstring>
#include <gtest/gtest.h>
#include <utils/matrix.hpp>
#include <utils/csv.hpp>

TEST ( matrix_test, basic )
{
    estd::matrix<double> m {
        {1, 2, 3},
        {4, 6, 7},
        {7, 8, 11}
    };

}

TEST ( csv_parser, basic )
{
    auto result = csv::parse ( "test.csv" );

    const estd::matrix<std::string> expected {
        {"empty", "empty", "wall"},
        {"empty", "wall", "wall"},
        {"wall", "empty", "wall"}
    };

    EXPECT_EQ ( 0, std::memcmp ( &result, &expected, sizeof ( result ) ) );
}

TEST ( csv_parser, fail_to_open_and_throw )
{
    EXPECT_THROW ( csv::parse ( "non_existant.csv" ), std::runtime_error );
}
