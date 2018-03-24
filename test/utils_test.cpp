
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

TEST ( csv_parser, parsing_and_equality )
{
    auto result = csv::parse ( "test.csv" );

    const estd::matrix<std::string> expected {
        {"empty", "empty", "wall"},
        {"empty", "wall", "wall"},
        {"wall", "empty", "wall"}
    };

    const estd::matrix<std::string> unexpected {
        {"empty", "empty", "wall"},
        {"empty", "wall", "empty"},
        {"wall", "empty", "wall"}
    };

    EXPECT_TRUE ( result == expected );
    EXPECT_TRUE ( result != unexpected );
    EXPECT_FALSE ( result != expected );
    EXPECT_FALSE ( result == unexpected );
}

TEST ( csv_parser, fail_to_open_and_throw )
{
    EXPECT_THROW ( csv::parse ( "non_existant.csv" ), std::runtime_error );
}
