#include "parser.h"
#include "flight_router.h"

#include <iostream>
#include <string>

int main() {
    auto flights = ParseFile("C:\\Users\\Lenovo\\Downloads\\flight_router\\T_T100_SEGMENT_ALL_CARRIER.csv"s);
    auto flight_router = FlightRouter(flights);

    std::string continue_searching = "y"s;

    while (continue_searching == "y"s) {
        std::string origin_city_name;
        std::string dest_city_name;

        std::cout << "Enter origin city name: "s;
        std::getline(std::cin, origin_city_name);
        std::cout << "Enter destination city name: "s;
        std::getline(std::cin,dest_city_name);

        auto route = flight_router.BuildRoute(origin_city_name, dest_city_name);
        if (route) {
            std::cout << "Total time required: "s << route->total_time << "\n"s
                      << "Route details: "s << std::endl;

            for (const auto& flight: route->items) {
                std::cout << flight << std::endl;
            }
        } else {
            std::cout << "No route from origin city to destination city"s << std::endl;
        }

        std::cout << "Would you like to continue?(y/n)"s << std::endl;
        std::getline(std::cin, continue_searching);
    }
}