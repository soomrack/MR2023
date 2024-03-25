#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include "Graph/Graph.hpp"


inline void parse_line(std::stringstream& line_stream, graph::Graph& graph) 
{
    static graph::CityID origin;
    static graph::CityID destination;
    static graph::Distance distance;
    std::string origin_name;

    std::string cell;
    for (int idx = 0; std::getline(line_stream, cell, ','); ++idx) 
    {
        while (std::ranges::count(cell, '"') % 2) {
            std::string temp_cell;
            std::getline(line_stream, temp_cell, ',');
            cell.append( ',' + temp_cell);
        }

        try
        {
            switch (idx)
            {
            case 7:
                distance = static_cast<graph::Distance>(stoi(cell));
                break;
            case 20:
                origin = static_cast<graph::CityID>(stoi(cell));
                break;
            case 31:
                destination = static_cast<graph::Distance>(stoi(cell));
                break;
            case 23:
                origin_name = cell;
                break;
            default:
                break;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << " idx: " << idx << " cell: \"" << cell << "\"" << '\n';
            return;
        }
    }

    graph.add_link(origin, destination, distance);
    graph[origin].city_name = origin_name;
}


graph::CityID choose_node(const std::unordered_set<graph::CityID>& reachable, graph::Graph& graph, const graph::CityID& goal)
{
    graph::Distance min_cost = std::numeric_limits<graph::Distance>::max();
    graph::CityID result;
    
    for (const graph::CityID& point: reachable) {

        graph::Distance node_cost = graph[point].distance;

        if (node_cost < min_cost) {
            min_cost = node_cost;
            result = point;
        }
    }

    return result;
}


std::vector<graph::CityID> find_path(graph::Graph& graph, const graph::CityID& start, const graph::CityID& goal)
{
    graph::Node& start_node = graph[start];
    start_node.distance = 0;
    start_node.previous = start;

    std::unordered_set<graph::CityID> reachable = {start};
    std::unordered_set<graph::CityID> explored;
    
    while (!reachable.empty()) {

        //Choose some node we know how to reach
        graph::CityID node_point = choose_node(reachable, graph, goal);
        graph::Node& node = graph[node_point];

        // If we just got to the goal node, build and return the path
        if (node_point == goal)
            return graph.build_path(goal);

        reachable.erase(node_point);
        explored.insert(node_point);

        // Where can we get from here that we haven't explored before?
        for (const auto& [adjacent, cost]: graph.get_adjacent_nodes(node_point)) {

            if (explored.count(adjacent)) continue;
            
            if (!reachable.count(adjacent)) {
                graph.init_node(adjacent);
                reachable.insert(adjacent);
            }

            graph::Distance adjacent_path_cost = node.reachable[adjacent];
            graph::Node& adjacent_node = graph[adjacent];
        
            // If this is a new path, or a shorter path than what we have, keep it.
            if (node.distance + adjacent_path_cost < adjacent_node.distance) {
                adjacent_node.previous = node_point;
                adjacent_node.distance = node.distance + adjacent_path_cost;
            }
        }
    }

    // If we get here, no path was found
    return std::vector<graph::CityID> {};
}


int main()
{
    std::ifstream datafile;
    datafile.open("../data.csv");

    std::ofstream logfile;
    logfile.open("../logfile.txt");
    
    if (!logfile.is_open()) {
        std::cerr << "Couldn't open logfile" << std::endl;
        return 0;
    }

    if (!datafile.is_open()) {
        std::cerr << "Couldn't open datafile" << std::endl;
        return 0;
    }
    
    graph::Graph city_graph;
    city_graph.reserve(526832);
    
    std::string csvline;
    std::getline(datafile, csvline); // pass first line

    while(std::getline(datafile, csvline)) {
        std::stringstream line_stream(csvline);
        parse_line(line_stream, city_graph);
    }

    datafile.close();
    logfile.close();

    std::cout << "Read success!" << '\n';

    for(graph::CityID city: find_path(city_graph, 1025702, 1410702)) {
        std::cout << "ID: " << city << " Name: " << city_graph[city].city_name 
        << " Distance: " << city_graph[city].distance << std::endl;
    }

    return 0;
}