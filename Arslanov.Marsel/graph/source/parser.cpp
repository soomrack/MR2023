#include "parser.hpp"

void Parser::parse(const std::string& file) {
    std::ifstream filestream;
    filestream.open(file);

    if (!filestream.is_open()) {
        // throw exception
    }

    flights.clear();
    size = 0;

    std::string line;
    std::string temp;

    double air_time;
    std::string unique_carrier_name, origin_city, dest_city;
    uint16_t departures, airline_id, origin_city_market_id, desk_city_market_id;

    const size_t departures_offset = 2, air_time_offset = 8,
                 airline_id_offset = 2, dest_city_market_id_offset = 11;
    size_t origin_city_market_id_offset;

    while (!filestream.eof()) {
        getline(filestream, line);
        std::stringstream input(line);

        for (size_t i = 0; i < departures_offset; i++)
            getline(input, temp, ',');
        departures = atoi(temp.c_str());

        for (size_t i = 0; i < air_time_offset; i++) getline(input, temp, ',');
        air_time = atof(temp.c_str());

        for (size_t i = 0; i < airline_id_offset; i++)
            getline(input, temp, ',');
        airline_id = atoi(temp.c_str());

        getline(input, unique_carrier_name, ',');

        if (unique_carrier_name[0] == '\"') {
            unique_carrier_name.erase(0, 1);
            origin_city_market_id_offset = 11;
        } else
            origin_city_market_id_offset = 9;
        for (size_t i = 0; i < origin_city_market_id_offset; i++)
            getline(input, temp, ',');
        origin_city_market_id = atoi(temp.c_str());

        getline(input, origin_city, ',');

        for (size_t i = 0; i < dest_city_market_id_offset; i++)
            getline(input, temp, ',');
        desk_city_market_id = atoi(temp.c_str());

        getline(input, dest_city, ',');

        if (air_time > 0 && departures > 0) {
            Flight flight;

            flight.air_time = air_time;
            flight.airline_id = airline_id;
            flight.unique_carrier_name = unique_carrier_name;
            flight.origin_city_market_id = origin_city_market_id;
            flight.dest_city_market_id = desk_city_market_id;
            flight.origin_city = origin_city;
            flight.dest_city = dest_city;

            flights.push_back(flight);
            size++;
        }
    }

    filestream.close();
}

void Parser::convert(const std::string& file) {
    std::ofstream filestream;
    filestream.open(file);

    if (!filestream.is_open()) {
        // throw exception
    }

    for (const Flight& flight : flights)
        filestream << flight.air_time << "\t" << flight.airline_id << "\t"
                   << flight.unique_carrier_name << "\t"
                   << flight.origin_city_market_id << "\t"
                   << flight.dest_city_market_id << "\t" << flight.origin_city
                   << "\t" << flight.dest_city << "\t" << std::endl;

    filestream.close();
}
