#ifndef BLAVENCIA_UTILS_CSV_HPP
#define BLAVENCIA_UTILS_CSV_HPP

#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "utils/matrix.hpp"

namespace csv {
estd::matrix<std::string> parse ( const std::string & filepath )
{
    std::ifstream is { filepath.c_str() };
    if ( !is.is_open() ) {
        const std::string msg = "Could not open " + filepath;
        throw std::runtime_error ( msg );
    }

    is.seekg ( 0, std::ios::end );
    const auto rows = is.tellg();
    is.seekg ( 0, std::ios::beg );

    estd::matrix<std::string> result;
    result.reserve ( rows );

    std::string line;
    while ( std::getline ( is, line ) ) {
        std::vector<std::string> split_line;
        boost::split ( split_line, line, boost::is_any_of ( "," ) );
        result.push_back ( split_line );
    }

    return result;
}
}

#endif // BLAVENCIA_UTILS_CSV_HPP

