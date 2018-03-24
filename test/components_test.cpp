#include "gtest/gtest.h"
#include <components/map.hpp>
#include <components/character.hpp>
#include <utils/csv.hpp>

TEST ( map, from_csv )
{
    map_t map {csv::parse ( "test.csv" ), {5, 5}};
}

TEST ( cell, from_string )
{
    std::string s {"wall"};
    cell_t cell ( s );
}

TEST ( character, construction )
{
    character_t c {{1, 1}};
}
