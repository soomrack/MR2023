#include "parser.h"

void Parser::pars(const std::string &file) {
    std::ifstream filestream;
    filestream.open(file);

    if (!filestream.is_open())
        throw ParserException("Could not open filestream to pars");

    flights.clear();
    size = 0;

    std::string line;
    std::string temp;

    double air_time;
    std::string unique_carrier_name, origin_city, dest_city;
    uint16_t departures, airline_id, origin_city_market_id, desk_city_market_id;

    const size_t departures_offset = 1, air_time_offset = 9, airline_id_offset = 11, dest_city_market_id_offset = 32;
    size_t origin_city_market_id_offset;

    while(getline(filestream, line)) {
        std::vector<std::string> result = split(input, delimiter);

        departures = atoi(result[departures_offset].c_str());
        air_time = atof(result[air_time_offset].c_str());
        airline_id = atoi(result[airline_id_offset].c_str());
        unique_carrier_name = result[airline_id_offset+1];

        if (unique_carrier_name[0] == '\"') {
            unique_carrier_name.erase(0, 1);
            origin_city_market_id_offset = 21;
        }
        else origin_city_market_id_offset = 19;
        origin_city_market_id = atoi(result[origin_city_market_id_offset].c_str());

        origin_city = result[origin_city_market_id_offset+1];
        desk_city_market_id = atoi(result[dest_city_market_id_offset].c_str());
        dest_city = result[dest_city_market_id_offset+1];

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

    filestream.close();;
}

void Parser::compos(const std::string &file) {
    std::ofstream filestream;
    filestream.open(file);

    if (!filestream.is_open())
        throw ParserException("Could not open filestream to compos");

    for (const Flight &flight: flights)
        filestream << flight.air_time << "\t"
                   << flight.airline_id << "\t"
                   << flight.unique_carrier_name << "\t"
                   << flight.origin_city_market_id << "\t"
                   << flight.dest_city_market_id << "\t"
                   << flight.origin_city << "\t"
                   << flight.dest_city << "\t"
                   << std::endl;

    filestream.close();;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}