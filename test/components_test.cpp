#include "gtest/gtest.h"
#include <components/map.hpp>
#include <components/character.hpp>
#include <utils/csv.hpp>

TEST ( map, from_csv )
{
    textures::texture_map textures;
    textures["empty"] = sf::Texture{};
    textures["wall"] = sf::Texture{};

    map_t map {csv::parse ( "test.csv" ), {5, 5}, textures};
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
