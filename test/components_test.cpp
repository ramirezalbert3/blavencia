#include "gtest/gtest.h"
#include <components/map.hpp>
#include <utils/csv.hpp>

TEST ( map, from_csv )
{
    map_t map {csv::parse ( "test.csv" )};
}

TEST ( cell, from_string )
{
    std::string s {"wall"};
    cell_t cell ( s );
}
