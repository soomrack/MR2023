#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>

namespace DjikstraAirlanesParser {

    using Time = uint32_t;

    enum class CsvLineState {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };


    enum class DataType {
        Dirty = 1,
        Cleared = 2
    };


    struct Flight {
        
        Time air_time{0};
        std::string origin_city{0};
        std::string dest_city{0};

        Flight() = default;
        Flight(Time air_time, std::string origin_city, std::string dest_city): 
            air_time{air_time}, origin_city{origin_city}, dest_city{dest_city} {}


        friend  std::ostream& operator<<(std::ostream& os, const Flight& flight) {
            return os << "ORIGIN CITY: " << flight.origin_city << "\t"
            << "DEST_CITY: " << flight.dest_city << "\t" << "AIR TIME: "
            << flight.air_time << "\n";
        }

    };  //  struct Flight


    class FlightParser {
 
    private:
        std::vector<Flight> flights;
        std::map<std::string, int> csv_header;
        std::string cleared_data_path;
        

    public:
        FlightParser() = delete;
        FlightParser(const std::string& path, DataType dtype);
        ~FlightParser() = default;

        const Flight& operator[](const size_t idx) const;
        inline std::vector<Flight>& get_flights() { return flights; }

    private:
        int scan_file(std::ifstream* filestream, const std::string& path);

        template<DataType dtype>
        void parse(std::ifstream* filestream, const std::string& path);

        void allocate(int sz);
        void parse_csv_header(const std::string& header_line);
        void append_cleared_header(const std::string& source_path);
        void append_cleared_data_file();
        bool check_data_line(std::vector<std::string>& flight_line, size_t line_idx);
        std::vector<std::string> csv_stacker(const std::string& line);
    
        friend std::ostream& operator<<(std::ostream& os, FlightParser& parser) {
            for (auto flight: parser.flights) {
                os << flight;
            }
            return os;
        }

    };  //  class FlightParser

};  //  namespace DjikstraAirlanesParser