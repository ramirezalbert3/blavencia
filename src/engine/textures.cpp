#include "engine/textures.hpp"

textures::texture_map textures::load_texture_map ( const textures::texture_pairs & pairs )
{
    textures::texture_map textures;

    for ( auto & pair : pairs ) {
        sf::Texture temporary;
        const std::string dat_path = DBG_DAT_PATH;
        const std::string filepath = dat_path + "/textures/" + pair.second + ".jpg";
        const bool texture_loaded = temporary.loadFromFile ( filepath );
        if ( !texture_loaded ) {
            const std::string msg = "Could not open " + filepath;
            throw std::runtime_error ( msg );
        }
        textures[pair.first] = temporary;
    }
    return textures;
}
