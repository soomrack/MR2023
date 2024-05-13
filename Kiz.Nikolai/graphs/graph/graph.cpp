#include "graph.hpp"
#include <iostream>

namespace DjikstraAirlanes {

    Airliner::Airliner(const std::string& log_path): parser{log_path} {
        compose();
    }


    void Airliner::compose() {
        auto flights = parser.get_flights();
        for (auto flight: flights) {
            ad_list[flight.origin_city].emplace_back(flight.dest_city, flight.air_time);
            ad_list[flight.dest_city].emplace_back(flight.origin_city, flight.air_time);
        }
    }

    void Airliner::print_graph() {
        for (auto value_type: ad_list) {
            std::cout << "[" << value_type.first;
            for (Neighbour n: value_type.second) {
                std::cout << " NEIGHBOUR: " <<  n.neighbour_city << " " << n.time << std::endl;
            }
            std::cout << "]\n";
        }
    }

};  //  namespace DjikstraAirlanes