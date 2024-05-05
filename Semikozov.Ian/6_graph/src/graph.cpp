#include "graph.hpp"

#include <algorithm>

static inline double cost(vertex &lhs, vertex &rhs)
{
    return std::sqrt(std::pow(lhs.value.first - rhs.value.first, 2) + std::pow(lhs.value.second - rhs.value.second, 2));
}

graph::graph(std::vector<std::vector<double>> adj) {}

graph::~graph()
{
    for (auto it : vmap) { delete it.second; }
    vmap.clear();
}

vertex *graph::at(size_t index) const
{
    return vmap.at(index);
}

size_t graph::index(vertex *vertex) const
{
    auto it = std::find_if(vmap.begin(), vmap.end(), [vertex](const auto &x) { return x.second == vertex; });
    return it->first;
}

size_t graph::size() const
{
    return vmap.size();
}

/// \brief Add edge
void graph::add(const size_t from, const size_t to, const double cost)
{
    auto *f = (vmap.find(from)->second), *t = (vmap.find(to)->second);
    edge edge = std::make_pair(cost, t);
    f->adjacency.push_back(edge);
}

/// \brief Add vertex
bool graph::add(size_t index, const point &point)
{
    VMap::iterator it = vmap.find(index);

    if (it != vmap.end()) { return false; }
    auto *new_ = new vertex{ point };
    vmap[index] = new_;

    return true;
}

/// \brief Updating adjacency matrix and fill edge vector
void graph::update()
{
    size_t gSize = vmap.size();

    for (int i = 0; i < gSize; i++)
    {
        vertex *lhs = vmap.at(i);

        for (size_t j = 0; auto it : vmap)
        {
            vertex *rhs = it.second;

            double c = cost(*lhs, *rhs);
            this->add(i, it.first, c == 0 ? infinity : c);
        }

        std::sort(lhs->adjacency.begin(), lhs->adjacency.end(), [](const auto &l, const auto &r) { return l.first > r.first; });
    }
}

bool graph::remove(size_t index)
{
    VMap::iterator i = vmap.find(index);
    if (i != vmap.end())
    {
        auto v = std::move(i->second);
        vmap.erase(i);
        delete v;

        return true;
    }

    return false;
}

spanning_tree graph::find_spanning_tree(size_t indexA, size_t indexB) const {}
