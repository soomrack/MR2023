#pragma once

#include "graph.h"
#include "router.h"
#include "parser.h"

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
    
class FlightRouter {
public:
    FlightRouter(std::vector<Flight> flights);
    
    struct RouteInfo {
        std::vector<Flight> items;
        double total_time;
    };
    
    std::optional<RouteInfo> BuildRoute(const std::string& from, const std::string& to) const;
    size_t GetCityIdByName(const std::string& city_name) const;
    
private:
    const std::vector<Flight> flights_;
    std::unordered_map<std::string, size_t> cities_;
    Graph graph_;
    Router flight_router_;
    
    Graph& InitializeInternalData();
    
};


FlightRouter::FlightRouter(std::vector<Flight> flights)
    : flights_(std::move(flights))
    , flight_router_(InitializeInternalData()) {
}

size_t FlightRouter::GetCityIdByName(const std::string& city_name) const {
    return cities_.at(city_name);
}

std::optional<FlightRouter::RouteInfo> FlightRouter::BuildRoute(const std::string& from, const std::string& to) const {
    auto from_id = GetCityIdByName(from);
    auto to_id = GetCityIdByName(to);
    auto route = flight_router_.BuildRoute(from_id, to_id);
    
    if (!route) {
        return std::nullopt;
    }
    
    RouteInfo route_info;
    route_info.total_time = route->weight;
    for (auto edge_id: route->edges) {
        route_info.items.push_back(flights_.at(edge_id));
    }
    return route_info;
}

Graph& FlightRouter::InitializeInternalData() {
    for (size_t i = 0; i != flights_.size(); ++i) {
        auto flight = flights_.at(i);
        
        if (!cities_.count(flight.origin_city_name)) {
            cities_[flight.origin_city_name] = cities_.size();
        }
        
        if (!cities_.count(flight.dest_city_name)) {
            cities_[flight.dest_city_name] = cities_.size();
        }
    }
        
    Graph graph(cities_.size());
    for (const auto& flight: flights_) {
        Edge edge;
        edge.weight = flight.air_time;
        edge.from = GetCityIdByName(flight.origin_city_name);
        edge.to = GetCityIdByName(flight.dest_city_name);
        graph.AddEdge(edge);    
    }        
    
    graph_ = std::move(graph);
    return graph_;
}