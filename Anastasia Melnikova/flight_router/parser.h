#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Flight {
    string origin_city_name;
    string dest_city_name;
    double air_time;
};

std::ostream& operator<<(std::ostream& os, const Flight& flight) {
    os << "City start: "s << flight.origin_city_name << "\n"s
         << "City end  : "s << flight.dest_city_name << "\n"s
         << "Time      : "s << flight.air_time << "\n"s;

    return os;
}

Flight ParseLine(const string& line) {
    Flight flight;

    size_t pos = 0;
    for (int i = 0; i != 9; ++i) {
        pos = line.find(","s, pos + 1);
    }

    size_t next_pos = line.find(","s, pos + 1);
    string time_str = line.substr(pos + 1, next_pos - pos);
    flight.air_time = stod(time_str);

    pos = line.find("\""s, next_pos + 1);
    next_pos = line.find("\""s, pos + 1);
    flight.origin_city_name = line.substr(pos + 1, next_pos - pos - 1);

    pos = line.find("\""s, next_pos + 1);
    next_pos = line.find("\""s, pos + 1);
    flight.dest_city_name = line.substr(pos + 1, next_pos - pos -1);
    

    return flight;
}

vector<Flight> ParseFile(const string& filename) {
    ifstream inputfile;
    inputfile.open(filename);

    vector<Flight> flights;
    string line;
    getline(inputfile, line);
    while (getline(inputfile, line)) { 
        Flight flight = ParseLine(line);

        if (flight.origin_city_name == flight.dest_city_name || flight.air_time == 0) {
            continue;
        }
        
        flights.push_back(flight);
    }

    return flights;
}