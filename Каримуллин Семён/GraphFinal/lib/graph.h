#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <limits>
#include <algorithm>
#include <vector>
#include <unordered_map>

#include "parser.h"

class GraphException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit GraphException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> graph;
public:
    explicit Graph(const std::vector<Flight> &flights);

    void dijkstra(const std::string &origin, const std::string &dest) const;

    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> get_graph() const { return graph; }
};


#endif //GRAPH_H
