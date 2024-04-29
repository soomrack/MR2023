#include "graph.hpp"

#include <algorithm>

Edge Graph::nullEdge{ infinity, nullptr };

static inline double cost(Vertex &lhs, Vertex &rhs)
{
    return std::sqrt(std::pow((lhs.value.first - rhs.value.first), 2) + std::pow((lhs.value.second - rhs.value.second), 2));
}

Graph::~Graph()
{
    for (auto it : vmap) { delete it.second; }
    vmap.clear();
}

Graph::Graph(std::unique_ptr<Grid> &grid)
{
    size_t count = grid->size();

    for (size_t index = 0; auto point : *grid) { this->add(index++, point); }
    this->update();
}

void Graph::add(const size_t from, const size_t to, const double cost)
{
    Vertex *f = (vmap.find(from)->second), *t = (vmap.find(to)->second);

    Edge edge = std::make_pair(cost, t);
    f->adjacency.push_back(edge);
}

bool Graph::add(size_t index, const Point &point)
{
    VMap::iterator it = vmap.find(index);

    if (it != vmap.end()) { return false; }
    auto *new_ = new Vertex{ point };
    vmap[index] = new_;

    return true;
}

void Graph::update()
{
    size_t gSize = vmap.size();

    for (int i = 0; i < gSize; i++)
    {
        Vertex *lhs = vmap.at(i);

        for (size_t j = 0; auto it : vmap)
        {
            Vertex *rhs = it.second;

            double c = cost(*lhs, *rhs);
            this->add(i, it.first, c == 0 ? infinity : c);
        }

        std::sort(lhs->adjacency.begin(), lhs->adjacency.end(), [](const auto &l, const auto &r) { return l.first < r.first; });
    }
}

bool Graph::remove(size_t index)
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
