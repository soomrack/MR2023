#include "graph.hpp"
#include "debug.hpp"

#include <algorithm>
#include <limits>
#include <queue>

using namespace debug;

graph::graph(const desc::flight_v &flights)
{
    for (const auto &flight : flights)
    {
        g[flight->origin_city].emplace_back(flight->dest_city, flight->air_time);
        g[flight->dest_city].emplace_back(flight->origin_city, flight->air_time);
    }
}

std::unordered_map<std::string, graph::adj> graph::get() const
{
    return g;
}

void graph::dijkstra(const std::string &origin, const std::string &dest) const
{
    constexpr auto infinity = std::numeric_limits<double>::max();
    std::unordered_map<std::string, double> air_times;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>,
                        std::vector<std::pair<double, std::string>>,
                        std::greater<>>
        pq;

    for (const auto &node : g) { air_times[node.first] = infinity; }

    air_times[origin] = 0.;
    pq.emplace(0., origin);

    while (!pq.empty())
    {
        std::pair<double, std::string> current = pq.top();
        pq.pop();

        if (current.second == dest) { break; }

        for (const auto &air_time : g.at(current.second))
        {
            double new_air_time = air_times[current.second] + air_time.second;

            if (new_air_time < air_times[air_time.first])
            {
                air_times[air_time.first] = new_air_time;
                previous[air_time.first] = current.second;
                pq.emplace(new_air_time, air_time.first);
            }
        }
    }

    if (air_times[dest] == infinity)
    {
        throw std::runtime_error{ boost::str(fmt % sb[err] % "No path available") };
    }

    std::vector<std::string> path;
    std::string current = dest;

    while (current != origin)
    {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(origin);
    std::reverse(path.begin(), path.end());

    auto path_desc = boost::str(fmt % sb[info] % "Shortest path: ");
    for (const std::string &city : path) { path_desc.append(city).append(" "); }
    std::cout << path_desc << std::endl;

    auto time = std::to_string(air_times[dest]);
    path_desc = boost::str(fmt % sb[info] % "Total time: ").append(time);

    std::cout << path_desc << std::endl;
}
