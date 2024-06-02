#pragma once
#include "parser.hpp"

#include <map>

namespace DjikstraAirlanes {

    using namespace DjikstraAirlanesParser;

    using City = std::string;
    using Time_list = std::map<City, Time>;
    using Adjacency_list = std::map<City, Time_list>;
    using Checked_nodes = std::vector<bool>;
    using Parent_list = std::map<City, City>;
    using Neighbour = std::pair<City, Time>;
    using Path = std::pair<std::vector<Neighbour>, Time>;


    class PathFinder {

    private:
        FlightParser parser;
        Path path_solution;
        Adjacency_list adjacency_list;
        Parent_list parent_list;
        Time_list time_list;
        Checked_nodes checked_nodes;

        static constexpr Time INF{UINT32_MAX};
        static constexpr const char* NONE{"NONE"};

    public:
        PathFinder() = delete;
        PathFinder(const std::string& log_path, DataType dtype);
        ~PathFinder() = default;

        inline const Adjacency_list& get_graph() { return adjacency_list; }
        void find(const std::string& origin_city, const std::string& dest_city) noexcept;

        void print_graph_info() noexcept;
        void print_path() noexcept;

    private:
        void compose();
        void restore_path(const std::string& origin, const std::string& dest) noexcept;
        const Neighbour find_closest_city();

    };  //  class PathFinder

};  //  namespace DjikstraAirlanes