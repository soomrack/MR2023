#include "graph.hpp"
#include <iostream>

namespace DjikstraAirlanes {

    PathFinder::PathFinder(const std::string& log_path, DataType dtype): parser{log_path, dtype} {
        compose();
        checked_nodes = new bool[adjacency_list.size()];
    }


    void PathFinder::compose() {
        auto flights = parser.get_flights();
        for (auto& flight: flights) {
        adjacency_list.try_emplace(flight.origin_city);
        adjacency_list.try_emplace(flight.dest_city);    
        if (!adjacency_list[flight.origin_city].contains(flight.dest_city) ||
            adjacency_list[flight.origin_city][flight.dest_city] >= flight.air_time) {
            adjacency_list[flight.origin_city][flight.dest_city] = flight.air_time;
            }
        }
    }


    void PathFinder::print_graph_info() {
        std::cout << "Flights graph has " << adjacency_list.size() << " nodes.\n";
        for (auto node: adjacency_list) {
            std::cout << node.first << ": " << node.second.size() << " neighbour(s)\n";
        }

    }

    
    void PathFinder::find(const std::string origin_city, const std::string dest_city) {
        for (auto& node: adjacency_list) {
            time_list[node.first] = INF;
            parent_list[node.first] = NONE;
        }
        time_list[origin_city] = 0;
        parent_list[origin_city] = origin_city;
        for (size_t idx = 0; idx < adjacency_list.size(); ++idx) {
            auto [city, time] = find_closest_city();
            for (auto& [neighbour, neighbour_time]:adjacency_list[city]) {
                if (time_list[neighbour] > neighbour_time + time) {
                    time_list[neighbour] = neighbour_time + time;
                    parent_list[neighbour] = city;
                }
            }
        }
        restore_path(origin_city, dest_city);
    }

    const Neighbour PathFinder::find_closest_city() {
        Time min_time = INF;
        City closest_city = NONE;
        size_t idx_to_toggle = -1;
        for (std::size_t idx = 0; auto& node: time_list) {
            if (!checked_nodes[idx] && node.second < min_time) {
                min_time = node.second;
                closest_city = node.first;
                idx_to_toggle = idx;
            }
            ++idx;
        }
        checked_nodes[idx_to_toggle] = true;
        return {closest_city, min_time};
    }

    void PathFinder::restore_path(const std::string& origin, const std::string& dest) {
        path_solution.second = 0;
        std::string node = dest;
        while (node != origin) {
            std::string& next = parent_list[node];
            if (next == NONE) {
                std::cout << "No path.\n";
                path_solution.second = INF;
                return;
            }
            auto time = time_list[node];
            path_solution.first.insert(path_solution.first.begin(), Neighbour(node, time));
            path_solution.second += time;
            node = next;
        }
        path_solution.first.insert(path_solution.first.begin(), Neighbour(node, time_list[node]));
    }


    void PathFinder::print_path() {
        if (path_solution.first.empty() || path_solution.second == INF) {
            std::cout << "There is no path between cities.\n";
            return;
        }
        std::cout << path_solution.first.front().first << " -> ";
        for (auto path_node = (path_solution.first.begin() + 1);  path_node != path_solution.first.end(); ++path_node) {
            std::cout << (*path_node).first << " | " << (*path_node).second << " -> ";
        }     
    }     

    PathFinder::~PathFinder() {
        delete[] checked_nodes;
    }

};  //  namespace DjikstraAirlanes