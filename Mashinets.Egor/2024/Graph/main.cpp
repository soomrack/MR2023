#include "parser.h"
#include "graph.h"

int main() {
    Parser parser;

    parser.pars("data.csv");
    parser.compos("data.txt");
    std::cout << "Flights parsed: " << parser.get_size() << std::endl;


    Graph graph(parser.get_flights());

    //Holy Cross (Alaska)--> Seattle (Washington)
    graph.dikstra("HCR", "SEA");

    return 0;
}