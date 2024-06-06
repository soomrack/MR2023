#include "graph.hpp"
#include "parser.hpp"

int main() {
    Parser parser;
    parser.parse("/home/marsel/Polikek/programming/graph/data.csv");
    parser.convert("durty_data.txt");
    std::cout << "Flights parsed: " << parser.get_size() << std::endl;
    Graph graph(parser.get_flights());
    graph.dijkstra("BTI", "SEA");

    return 0;
}