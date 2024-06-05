#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>

#include "description.hpp"

class graph
{
private:
    using edge = std::pair<std::string, double>;
    using adj = std::vector<edge>;

    std::unordered_map<std::string, adj> g;

public:
    explicit graph(const desc::flight_v &flights);
    ~graph() = default;

    void dijkstra(const std::string &origin, const std::string &dest) const;
    std::unordered_map<std::string, adj> get() const;
};

#endif // GRAPH_HPP
