#pragma once
#include "parser.hpp"
#include <unordered_map>

namespace DjikstraAirlanes {

    struct Neighbour {
        std::string neighbour_city{0};
        uint16_t time{0};
    };  //  struct Neighbour

    using namespace DjikstraAirlanesParser;
    using city = std::string;
    using adjacency_list = std::unordered_map<city, std::vector<Neighbour>>;
    using parent_list = std::unordered_map<city, city>;

    using path = std::pair<std::vector<Neighbour>, uint16_t>;
    // uint16_t INF = UINT16_MAX;

    class Airliner {

    private:
        FlightParser parser;
        path current_path;
        adjacency_list ad_list;



    public:
        Airliner() = delete;
        Airliner(const std::string& log_path);
        ~Airliner() = default;
        path find_path(std::string origin_city, std::string dest_city);
        void print_graph();

    private:
        void compose();

    };  //  class Airliner

};  //  namespace DjikstraAirlanes