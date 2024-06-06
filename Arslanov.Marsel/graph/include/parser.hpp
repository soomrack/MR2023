#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Flight {
    double air_time;
    uint16_t airline_id;
    std::string unique_carrier_name;
    uint16_t origin_city_market_id;
    uint16_t dest_city_market_id;
    std::string origin_city;
    std::string dest_city;
};

class Parser
{
private:
    std::vector<Flight> flights;
    size_t size;

public:
    void parse(const std::string& file);

    void convert(const std::string& file);

    std::vector<Flight> get_flights() { return flights; };

    unsigned long get_size() const { return size; };
};
