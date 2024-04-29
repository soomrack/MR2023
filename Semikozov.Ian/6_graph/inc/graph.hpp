#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <algorithm>
#include <atomic>
#include <cmath>
#include <map>
#include <memory>
#include <utility>
#include <vector>

struct Vertex;
class Graph;

using Point = std::pair<double, double>;
using Edge = std::pair<double, Vertex *>;
using Grid = std::vector<Point>;

struct Vertex
{
    std::vector<Edge> adjacency;
    std::atomic_bool visited{ false };
    Point value;

    Vertex(const Point &v) : value(v) {}
    ~Vertex() {}
}; // struct Vertex

class Graph
{
    using VMap = std::map<size_t, Vertex *>;

    static constexpr double infinity{ std::numeric_limits<double>::max() };

public:
    static Edge nullEdge;

public:
    Graph() = default;
    Graph(std::unique_ptr<Grid> &grid);
    ~Graph();

    /// \brief Add edge
    void add(const size_t from, const size_t to, const double cost);

    /// \brief Add vertex
    bool add(size_t index, const Point &point);
    bool remove(size_t index);

    inline Vertex *at(size_t index)
    {
        return vmap.at(index);
    }

    inline size_t index(Vertex *vertex)
    {
        auto it = std::find_if(vmap.begin(), vmap.end(), [vertex](const auto &x) { return x.second == vertex; });
        return it->first;
    }

    inline size_t size() const
    {
        return vmap.size();
    }

private:
    /// \brief Updating adjacency matrix and fill edge vector
    void update();

private:
    VMap vmap;

}; // class Graph

#endif // GRAPH_HPP_INCLUDED
