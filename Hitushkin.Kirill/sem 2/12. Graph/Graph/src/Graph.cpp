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


std::stack<CityID> Graph::build_path(const CityID& goal_node)
{
    std::stack<CityID> path;
    path.push(goal_node);

    CityID point = goal_node;

    while (true)
    {
        const Node& node = node_map[point];

        if (point == node.previous) break;

        point = node.previous;
        
        path.push(point);
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


void Graph::del_link(const CityID& origin, const CityID& dest)
{
    if (!node_map.count(origin)) init_node(origin);

    if (!node_map[origin].reachable.count(dest)) 
        throw GraphException(__FILE__, __LINE__, "This dest does not exist");

    node_map[origin].reachable.erase(dest);
}


void Graph::add_link(const CityID& node, const CityID& dest, const Distance& distance)
{
    if (!node_map.count(node)) init_node(node);

    Node& node_ptr = node_map[node];
    if (!node_ptr.reachable.count(dest) || node_ptr.reachable[dest] > distance) 
        node_ptr.reachable[dest] = distance;
}

std::stack<CityID> Graph::find_path(const CityID& start_point, const CityID& goal_point)
{
    init_node(start_point);
    // previous_ == this_point - stopping condition for build_path
    node_map[start_point].previous = start_point;

    auto comp = [](const PointTuple& pt1, const PointTuple& pt2)
    { 
        return std::get<1>(pt1) > std::get<1>(pt2); 
    };
    // PointTuple = {node, cost, previous_node}
    std::priority_queue<PointTuple, std::vector<PointTuple>, decltype(comp)> reachable(comp);
    reachable.push(std::make_tuple(start_point, 0, start_point));
    std::unordered_set<CityID> explored;
    
    while (!reachable.empty()) 
    {
        CityID node_point = std::get<0>(reachable.top());
        CityID previous_node_point = std::get<2>(reachable.top());
        reachable.pop();

        Node& node = node_map[node_point];
        Node& previous_node = node_map[previous_node_point];
        
        Distance new_cost;
        try
        {
            new_cost = previous_node.distance + previous_node.reachable.at(node_point);
        }
        catch(const std::exception& e)
        {
            new_cost = previous_node.distance;
        }

        if (explored.count(node_point)) {
            if (node.distance > new_cost) {
                // TODO costs update
                node.distance = new_cost;
                node.previous = previous_node_point;
            };
            continue;
        }
        explored.insert(node_point);

        node.distance = new_cost;
        node.previous = previous_node_point;

        // If we just got to the goal node, build and return the path
        if (node_point == goal_point)
            return build_path(goal_point);

        // Where can we get from here that we haven't explored before?
        for (const auto& [adjacent, adjacent_path_cost]: node.reachable) 
        {
            if (explored.count(adjacent)) continue;
            init_node(adjacent);
            reachable.push(std::make_tuple(adjacent,
                node.distance + adjacent_path_cost, node_point));    
        }
    }

    // If we get here, no path was found
    return std::stack<CityID> {};
}

}
