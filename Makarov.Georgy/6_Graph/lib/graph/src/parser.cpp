#include "parser.h"

void Parser::parse(const std::string &file) {
    std::ifstream filestream;
    filestream.open(file);

    if (!filestream.is_open())
        throw ParserException("Could not open filestream to parse");

    flights.clear();
    size = 0;

    std::string line;
    std::string temp;
    int departures;

    double air_time, airline_id, origin_city_market_id, desk_city_market_id;
    std::string unique_carrier_name, origin_city, dest_city;

    while (!filestream.eof()) {
        getline(filestream, line);
        std::stringstream input(line);

        for (size_t i = 0; i < 2; i++)
            getline(input, temp, ',');
        departures = atoi(temp.c_str());

        for (size_t i = 0; i < 8; i++)
            getline(input, temp, ',');
        air_time = atof(temp.c_str());

        for (size_t i = 0; i < 2; i++)
            getline(input, temp, ',');
        airline_id = atof(temp.c_str());

        getline(input, unique_carrier_name, ',');
        if (unique_carrier_name[0] == '"')
            unique_carrier_name.erase(0, 1);

        for (size_t i = 0; i < 9; i++)
            getline(input, temp, ',');
        origin_city_market_id = atof(temp.c_str());

        getline(input, origin_city, ',');

        for (size_t i = 0; i < 11; i++)
            getline(input, temp, ',');
        desk_city_market_id = atof(temp.c_str());

        getline(input, dest_city, ',');

        if (air_time > 0 && departures > 0) {
            Flight flight;

            flight.air_time = air_time;
            flight.airline_id = airline_id;
            flight.unique_carrier_name = unique_carrier_name;
            flight.origin_city_market_id = origin_city_market_id;
            flight.origin_city = origin_city;
            flight.dest_city_market_id = desk_city_market_id;
            flight.dest_city = dest_city;

            flights.push_back(flight);
            size++;
        }
    }

    filestream.close();;
}

void Parser::compose(const std::string &file) {
    std::ofstream filestream;
    filestream.open(file);

    if (!filestream.is_open())
        throw ParserException("Could not open filestream to compose");

    for (const Flight &flight: flights)
        filestream << flight.air_time << "\t"
                   << flight.airline_id << "\t"
                   << flight.unique_carrier_name << "\t"
                   << flight.origin_city_market_id << "\t"
                   << flight.origin_city << "\t"
                   << flight.dest_city_market_id << "\t"
                   << flight.dest_city << "\t"
                   << std::endl;

    filestream.close();;
}
