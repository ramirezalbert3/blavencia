#ifndef BLAVENCIA_ENGINE_TEXTURES_HPP
#define BLAVENCIA_ENGINE_TEXTURES_HPP

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

namespace textures {

using texture_map = std::map<std::string, sf::Texture>;
using texture_pairs = std::vector<std::pair<std::string, std::string>>;

texture_map load_texture_map ( const texture_pairs & pairs );

}

#endif // BLAVENCIA_ENGINE_TEXTURES_HPP

