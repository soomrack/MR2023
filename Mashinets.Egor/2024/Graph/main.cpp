#include "parser.h"
#include "graph.h"

int main() {
    Parser parser;

    // Parse file (ignored by .gitignore to prevent repository size expansion)
    parser.parse("data.csv");
    parser.compose("data.txt");
    std::cout << "Flights parsed: " << parser.get_size() << std::endl;


    Graph graph(parser.get_flights());

    // From Holy Cross (Alaska, US) to Seattle (Washington, US)
    graph.dijkstra("HCR", "SEA");

    return 0;
}