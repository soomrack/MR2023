#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

#include "parser.hpp"

class Graph
{
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>
        graph;

public:
    explicit Graph(const std::vector<Flight>& flights);

    void dijkstra(const std::string& origin, const std::string& dest) const;

    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>
    get_graph() const {
        return graph;
    }
};
