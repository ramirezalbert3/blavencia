#include "gtest/gtest.h"
#include <components/map.hpp>
#include <utils/csv.hpp>

TEST ( map, from_csv )
{
    auto result = csv::parse ( "test.csv" );
//     map_t map{result};
}

