#ifndef BLAVENCIA_UTILS_CSV_HPP
#define BLAVENCIA_UTILS_CSV_HPP

#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include <boost/tokenizer.hpp>
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

    const auto rows = std::count ( std::istreambuf_iterator<char> ( is ),
                                   std::istreambuf_iterator<char>(), '\n' );
    is.seekg ( 0, std::ios::beg );

    estd::matrix<std::string> result;
    result.reserve ( rows );

    using csv_tokenizer = boost::tokenizer<boost::escaped_list_separator<char>>;

    for ( std::string line; std::getline ( is, line ); ) {
        boost::erase_all ( line, " " );
        if ( boost::algorithm::ends_with ( line, "," ) ) line.pop_back();
        csv_tokenizer tok ( line );
        std::vector<std::string> split_line {tok.begin(), tok.end() };
        result.push_back ( split_line );
    }

    return result;
}
}

#endif // BLAVENCIA_UTILS_CSV_HPP
