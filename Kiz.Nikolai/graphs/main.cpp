#include <iostream>
#include <filesystem>
#include "parser.hpp"
#include "graph.hpp"


using namespace DjikstraAirlanesParser;
using namespace DjikstraAirlanes;

int main() {
    std::string path((std::filesystem::current_path().parent_path() / "dataworker" / "T_T100_SEGMENT_ALL_CARRIER_cleared.csv").string());

    PathFinder djikstra(path, DataType::Cleared);
    djikstra.find("Talkeetna, AK", "Sidney, MT");
    djikstra.print_path();
}
