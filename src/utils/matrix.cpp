#include <fstream>
#include <boost/algorithm/string.hpp>

#include "utils/matrix.hpp"

using namespace estd;

template<class T, std::size_t R, std::size_t C>
matrix<T, R, C>::matrix ( const std::string& filepath )
{
    std::ifstream is;
    is.open ( filepath.c_str() );

    is.seekg ( 0, std::ios::end );
    const auto length = is.tellg();
    is.seekg ( 0, std::ios::beg );

    std::vector<std::string> strs;
    strs.reserve ( length );
//
//     boost::split(strs, "please split,this,csv,,line,", boost::is_any_of(","));
}
