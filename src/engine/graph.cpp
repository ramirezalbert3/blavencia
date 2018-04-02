#include "engine/graph.hpp"
#include "components/map.hpp"

/*
Needed returns
- graph
- vector of pairs<pair<it_row, it_col>, *vertice>
*/

graph::map_graph_t graph::create_graph ( const map_t& map )
{
    graph::map_graph_t graph { map.rows() * map.columns() };
    estd::matrix<bool> checked {std::vector<std::vector<bool>> {false}};

    const auto vertices_pair = vertices ( graph );
    auto vertice = vertices_pair.first;
    const auto& vertices_end = vertices_pair.second;

    // TODO(aramirez):
    // recursive check all cells
    // check all 4 cells surrounding, and if empty add_edge and then
    // call the function on that cell

    return graph;
};
