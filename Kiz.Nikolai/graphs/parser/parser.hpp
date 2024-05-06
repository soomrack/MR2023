#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>


namespace DjikstraAirlanesParser {

    enum class CsvLineStatus {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };


    struct Flight {
        
        friend  std::ostream& operator<<(std::ostream& os, const Flight& flight) {
            return os << "ORIGIN CITY: " << flight.origin_city << "\t"
            << "DEST_CITY: " << flight.dest_city << "\t" << "AIR TIME: "
            << flight.air_time << "\n";
        }

        uint16_t air_time{0};
        std::string origin_city{0};
        std::string dest_city{0};

        Flight() = default;
        Flight(uint16_t air_time, std::string origin_city, std::string dest_city): 
            air_time{air_time}, origin_city{origin_city}, dest_city{dest_city} {}

    };  //  struct Flight


    class FlightParser {

        friend std::ostream& operator<<(std::ostream& os, FlightParser& parser) {
            for (auto flight: parser.flights) {
                os << flight;
            }
            return os;
        }


    private:
        std::vector<Flight> flights;
        std::map<std::string, int> csv_header;


    public:
        FlightParser() = delete;
        FlightParser(const std::string& path);
        ~FlightParser() = default;

        const Flight& operator[](const size_t idx) const;
        inline std::vector<Flight>& get_flights() { return flights; }


    private:
        int scan_file(std::ifstream* filestream, const std::string& path);
        void parse(std::ifstream* filestream, const std::string& path);
        void allocate(int sz);
        void parse_header(const std::string& header_line);
        std::vector<std::string> csv_stacker(const std::string line);

    };  //  class FlightParser

};  //  namespace DjikstraAirlanesParser