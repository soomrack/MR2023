#include "parser.h"

int main() {
    Parser parser;

    parser.parse("data.csv");
    parser.compose("data.txt");

    std::cout << "Flights parsed: " << parser.get_size() << std::endl;

    return 0;
}