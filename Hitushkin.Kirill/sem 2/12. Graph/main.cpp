#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <chrono>
#include "Graph/Graph.hpp"

using namespace std::chrono;


inline void parse_line(std::stringstream& line_stream, graph::Graph& graph) 
{
    static graph::CityID origin;
    static graph::CityID destination;
    static graph::Distance distance;
    std::string origin_name;

    std::string cell;
    for (int idx = 0; std::getline(line_stream, cell, ','); ++idx) 
    {
        while (std::ranges::count(cell, '"') % 2) {
            std::string temp_cell;
            std::getline(line_stream, temp_cell, ',');
            cell.append( ',' + temp_cell);
        }

        try
        {
            switch (idx)
            {
            case 7:
                distance = static_cast<graph::Distance>(stoi(cell));
                break;
            case 20:
                origin = static_cast<graph::CityID>(stoi(cell));
                break;
            case 31:
                destination = static_cast<graph::Distance>(stoi(cell));
                break;
            case 23:
                origin_name = cell;
                break;
            default:
                break;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << " idx: " << idx << " cell: \"" << cell << "\"" << '\n';
            return;
        }
    }

    graph.add_link(origin, destination, distance);
    graph[origin].city_name = origin_name;
}


int main()
{
    std::ifstream datafile;
    datafile.open("../data.csv");

    if (!datafile.is_open()) {
        std::cerr << "Couldn't open datafile" << std::endl;
        return 0;
    }
    
    auto start = high_resolution_clock::now();

    graph::Graph city_graph;
    city_graph.reserve(526832);
    
    std::string csvline;
    std::getline(datafile, csvline); // pass first line

    while(std::getline(datafile, csvline)) {
        std::stringstream line_stream(csvline);
        parse_line(line_stream, city_graph);
    }

    auto stop = high_resolution_clock::now();

    datafile.close();

    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Read success! Time: " << duration.count() << " ms" << '\n';

    std::stack<graph::CityID> path = city_graph.find_path(1025702, 1410702);

    while (path.size())
    {
        graph::CityID city = path.top();
        std::cout << "ID: " << city << " Name: " << city_graph[city].city_name 
        << " Distance: " << city_graph[city].distance << std::endl;
        path.pop();
    }

    return 0;
}