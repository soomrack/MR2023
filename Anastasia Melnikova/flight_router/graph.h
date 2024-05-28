#pragma once

#include <vector>

#include "range.h"

using VertexId = size_t;
using EdgeId = size_t;

struct Edge {
    VertexId from;
    VertexId to;
    double weight;
};

class Graph {
private:
    using IncidenceList = std::vector<EdgeId>;
    using IncidentEdgesRange = Range<IncidenceList::const_iterator>;

public:
    Graph() = default;
    explicit Graph(size_t vertex_count);
    EdgeId AddEdge(const Edge& edge);

    size_t GetVertexCount() const;
    size_t GetEdgeCount() const;
    const Edge& GetEdge(EdgeId edge_id) const;
    IncidentEdgesRange GetIncidentEdges(VertexId vertex) const;
    std::vector<Edge> GetEdges() const;
    void SetEdges(const std::vector<Edge>& edges);
    std::vector<IncidenceList> GetIncidenceLists() const;
    void SetIncidenceLists(const std::vector<IncidenceList>& incidence_lists);

private:
    std::vector<Edge> edges_;
    std::vector<IncidenceList> incidence_lists_;
};

Graph::Graph(size_t vertex_count)
    : incidence_lists_(vertex_count) {
}

EdgeId Graph::AddEdge(const Edge& edge) {
    edges_.push_back(edge);
    const EdgeId id = edges_.size() - 1;
    incidence_lists_.at(edge.from).push_back(id);
    return id;
}

size_t Graph::GetVertexCount() const {
    return incidence_lists_.size();
}

size_t Graph::GetEdgeCount() const {
    return edges_.size();
}

const Edge& Graph::GetEdge(EdgeId edge_id) const {
    return edges_.at(edge_id);
}

Graph::IncidentEdgesRange Graph::GetIncidentEdges(VertexId vertex) const {
    return AsRange(incidence_lists_.at(vertex));
}

std::vector<Edge> Graph::GetEdges() const {
    return edges_;
}

void Graph::SetEdges(const std::vector<Edge>& edges) {
    edges_ = edges;
}

std::vector<Graph::IncidenceList> Graph::GetIncidenceLists() const {
    return incidence_lists_;
}

void Graph::SetIncidenceLists(const std::vector<Graph::IncidenceList>& incidence_lists) {
    incidence_lists_ = incidence_lists;
}
