#include "graph.hpp"
#include <iostream>

namespace DjikstraAirlanes {

    PathFinder::PathFinder(const std::string& log_path, DataType dtype): parser{log_path, dtype} {
        compose();
        checked_nodes.resize(adjacency_list.size(), false);
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


    void PathFinder::print_graph_info() noexcept {
        std::cout << "Flights graph has " << adjacency_list.size() << " nodes.\n";
        for (auto node: adjacency_list) {
            std::cout << node.first << ": " << node.second.size() << " neighbour(s)\n";
        }

    }

    
    void PathFinder::find(const std::string& origin_city, const std::string& dest_city) noexcept {
        for (auto& node: adjacency_list) {
            time_list[node.first] = INF;
            parent_list[node.first] = NONE;
        }
        time_list[origin_city] = 0;
        parent_list[origin_city] = origin_city;
        while (1) {
            auto [city, time] = find_closest_city();
            if (city == NONE && time == INF) { break; }
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
        size_t idx_to_toggle = SIZE_MAX;
        for (size_t idx = 0; auto& [city, time]: time_list) {
            if (!checked_nodes[idx] && time < min_time) {
                min_time = time;
                closest_city = city;
                idx_to_toggle = idx;
            }
            ++idx;
        }
        if (idx_to_toggle != SIZE_MAX) { checked_nodes[idx_to_toggle] = true; }
        return {closest_city, min_time};
    }

    void PathFinder::restore_path(const std::string& origin, const std::string& dest) noexcept {
        path_solution.second = 0;
        std::string node = dest;
        while (node != origin) {
            std::string& next = parent_list[node];
            if (next == NONE || next.empty()) {
                path_solution.second = INF;
                path_solution.first.clear();
                return;
            }
            auto time = time_list[node];
            path_solution.first.push_back({node,time});
            path_solution.second += time;
            node = next;
        }
        path_solution.first.push_back({node, time_list[node]});
        std::reverse(path_solution.first.begin(), path_solution.first.end());
    }


    void PathFinder::print_path() noexcept {
        if (path_solution.first.empty() || path_solution.second == INF) {
            std::cout << "There is no path between cities.\n";
            return;
        }

        for (auto node = path_solution.first.begin(); node != path_solution.first.end() - 1; node++) {
            std::cout << node->first << " -> "  << (node+1)->first <<  " (" << (node+1)->second << " mins) \n";
        }
        std::cout << "Total time: " << path_solution.second << " mins\n";     
    }     

};  //  namespace DjikstraAirlanes