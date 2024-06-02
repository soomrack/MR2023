#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct Flight {
    double air_time;
    uint16_t airline_id;
    std::string unique_carrier_name;
    uint16_t origin_city_market_id;
    uint16_t dest_city_market_id;
    std::string origin_city;
    std::string dest_city;
};

class ParserException : public std::exception {
private:
    std::string exception_msg;
public:
    explicit ParserException(std::string msg) : exception_msg(std::move(msg)) {}

    [[nodiscard]] const char *what() const noexcept override { return exception_msg.c_str(); }
};

class Parser {
private:
    std::vector<Flight> flights;
    size_t size;
public:
    void pars(const std::string &file);

    void compos(const std::string &file);

    std::vector<Flight> get_flights() { return flights; };

    [[nodiscard]] unsigned long get_size() const { return size; };

};

#endif //PARSER_H