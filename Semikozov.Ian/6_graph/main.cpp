#include "debug.hpp"
#include "graph.hpp"
#include "parser.hpp"

#include <boost/format.hpp>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;
using namespace debug;

/**
 * @brief call main with next arguments
 *
 * @param argv - [1] - path to CSV-table, [2] - origin city, [3] - destination city
 */
int main(int argc, const char **argv)
{
    if (argc != 4) { return 0; }

    const fs::path csv_table{ argv[1] };
    std::cout << fmt % sb[info] % "Parsing CSV-table with flights" << std::endl;
    auto flights = parser::parse(csv_table);

    parser::dump(flights, "data.txt");

    std::cout << fmt % sb[info] % "After parsing get flight count - " << flights.size()
              << std::endl;
    auto g = std::make_unique<graph>(flights);

    g->dijkstra(argv[2], argv[3]);

    return 0;
}
