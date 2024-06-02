#include "graph.h"

Graph::Graph(const std::vector<Flight> &flights) {
    for (const Flight &flight: flights) {
        graph[flight.origin_city].emplace_back(flight.dest_city, flight.air_time);
        graph[flight.dest_city].emplace_back(flight.origin_city, flight.air_time);
    }
}

void Graph::dikstra(const std::string &origin, const std::string &dest) const {
    std::unordered_map<std::string, double> air_times;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<>> pq;

    for (std::pair<std::string, std::vector<std::pair<std::string, double>>> node: graph)
        air_times[node.first] = std::numeric_limits<double>::max();

    air_times[origin] = 0.;
    pq.emplace(0., origin);

    while (!pq.empty()) {
        std::pair<double, std::string> current = pq.top();
        pq.pop();

        if (current.second == dest)
            break;

        for (const std::pair<std::string, double> &air_time: graph.at(current.second)) {
            double new_air_time = air_times[current.second] + air_time.second;

            if (new_air_time < air_times[air_time.first]) {
                air_times[air_time.first] = new_air_time;
                previous[air_time.first] = current.second;
                pq.emplace(new_air_time, air_time.first);
            }
        }
    }

    if (air_times[dest] == std::numeric_limits<double>::max())
        throw GraphException("No path available");

    std::vector<std::string> path;
    std::string current = dest;

    while (current != origin) {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(origin);
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest path: ";
    for (const std::string &city: path) std::cout << city << " -> ";
    std::cout << "\b\b\b\b" << std::endl << "Total time: " << air_times[dest] << std::endl;
}
