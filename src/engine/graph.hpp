#ifndef BLAVENCIA_ENGINE_GRAPH_HPP
#define BLAVENCIA_ENGINE_GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include "utils/matrix.hpp"

class map_t;

namespace graph
{
using map_graph_t = boost::adjacency_list<boost::vecS, boost::vecS,
      boost::undirectedS,
      boost::no_property,
      boost::no_property>;

map_graph_t create_graph ( const map_t& map );
}
#endif // BLAVENCIA_ENGINE_GRAPH_HPP

