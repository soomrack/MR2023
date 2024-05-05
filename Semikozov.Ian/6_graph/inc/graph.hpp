/**
 * @file graph.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 18.04.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <cmath>
#include <map>
#include <memory>
#include <utility>
#include <vector>

struct vertex;

using edge = std::pair<double, vertex *>;
using arcedge = std::pair<size_t, size_t>;
using point = std::pair<double, double>;
using spanning_tree = std::vector<arcedge>;

class graph
{
    using VMap = std::map<size_t, vertex *>;
    static constexpr double infinity{ std::numeric_limits<double>::infinity() };
    static constexpr edge null_edge{ infinity, nullptr };

public:
    graph() = default;
    graph(std::vector<std::vector<double>> adj);
    ~graph();

    void add(const size_t from, const size_t to, const double cost);
    bool add(size_t index, const point &point_);
    bool remove(size_t index);
    vertex *at(size_t index) const;
    size_t index(vertex *vertex) const;
    size_t size() const;

    spanning_tree find_spanning_tree(size_t indexA, size_t indexB) const;

private:
    void update();

private:
    mutable spanning_tree st;
    VMap vmap;
}; // class Graph

struct vertex
{
    std::vector<edge> adjacency;
    point value;

    vertex(const point &v) : value(v) {}
    ~vertex() {}
}; // struct Vertex

#endif // GRAPH_HPP_INCLUDED
