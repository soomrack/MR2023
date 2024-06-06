#include "parser.h"
#include "graph.h"

int main() {
    Parser parser;

    parser.pars("T_T100_SEGMENT_ALL_CARRIER copy.csv");
    parser.compos("composed_data.txt");
    std::cout << "Flights parsed: " << parser.get_size() << std::endl;

    Graph graph(parser.get_flights());

    graph.dijkstra("HCR", "SEA");

    return 0;
}