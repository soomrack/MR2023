#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphException.hpp"
#include "Node.hpp"

#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

namespace graph
{

class Graph
{
private:

    std::unordered_map<CityID, Node> node_map;

public:
    Graph();

    void reserve(const std::size_t size);

    Node& operator[](const CityID& key);

    std::stack<CityID> build_path(const CityID& goal_node);

    void init_node(const CityID& point);

    std::unordered_map<CityID, Distance>& get_adjacent_nodes(const CityID& node);

    void del_link(const CityID& origin, const CityID& link);
    void add_link(const CityID& origin, const CityID& link, const Distance& cost);

    std::stack<CityID> find_path(const CityID& start_point, const CityID& end_point);
    typedef std::tuple<CityID, Distance, CityID> PointTuple;
};

}

#endif
