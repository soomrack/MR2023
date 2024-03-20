#include "Graph/Graph.hpp"

#include <limits>


namespace graph
{

Graph::Graph() {}


void Graph::reserve(const std::size_t size) 
{
    node_map.reserve(size);
}


Node& Graph::operator[](const CityID& key)
{        
    if (!node_map.count(key)) init_node(key);

    return node_map[key];
}


std::vector<CityID> Graph::build_path(const CityID& goal_node)
{
    std::vector<CityID> path = { goal_node };

    CityID city_idx = goal_node;
    auto node = node_map.find(city_idx);

    while (city_idx != node->second.previous)
    {
        city_idx = node->second.previous;
        path.push_back(city_idx);
        node = node_map.find(city_idx);
    }
    
    return path;
}


std::unordered_map<CityID, Distance>& Graph::get_adjacent_nodes(const CityID& node)
{
    return node_map[node].reachable;
}


void Graph::init_node(const CityID& key)
{
    node_map[key].distance = std::numeric_limits<Distance>::max();
}


void Graph::del_link(const CityID& node, const CityID& link)
{
    if (!node_map.count(node)) init_node(node);

    if (!node_map[node].reachable.count(link)) 
        throw GraphException(__FILE__, __LINE__, "This link does not exist");

    node_map[node].reachable.erase(link);
}


void Graph::add_link(const CityID& node, const CityID& link, const Distance& distance)
{
    if (!node_map.count(node)) init_node(node);

    Node& node_ptr = node_map[node];
    if (!node_ptr.reachable.count(link) || node_ptr.reachable[link] > distance) 
        node_ptr.reachable[link] = distance;
}

}
