#include <iostream>
#include <filesystem>
#include "parser.hpp"
#include "graph.hpp"


using namespace DjikstraAirlanesParser;
using namespace DjikstraAirlanes;

int main() {
    std::string path = (std::filesystem::current_path() / "dataworker" / "cleared_data.csv").string();
    // FlightParser parser(path);
    // std::cout << parser;
    Airliner djikstra(path);
    // djikstra.compose();
    djikstra.print_graph();

}
