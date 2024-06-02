#include <iostream>
#include "parser.hpp"
#include "sstream"
#include "parserException.cpp"

using namespace DjikstraAirlanesParser;


template<>
void FlightParser::parse<DataType::Dirty>(std::ifstream* filestream, const std::string& path) {
    if(!filestream->is_open()) {
        try { 
            filestream->open(path);
        }
        catch (std::exception& e) {
            throw ParserException("Couldn't open a file.");
        } 
    }
    std::string line;
    std::getline(*filestream, line);
    parse_csv_header(line);
    append_cleared_header(path);
    size_t line_idx = 0;
    for (line; std::getline(*filestream, line, '\n'); ++line_idx) {
        auto result = csv_stacker(line);
        if (check_data_line(result, line_idx)) {
        flights.emplace_back(std::atoi(result[csv_header["AIR_TIME"]].c_str()),
                            result[csv_header["ORIGIN_CITY_NAME"]],
                            result[csv_header["DEST_CITY_NAME"]]);
            append_cleared_data_file();
        }

    }
    filestream->close();
    flights.shrink_to_fit();
    std::cout << "Flights after cleaning:" << flights.size() << "\n";
}


template<>
void FlightParser::parse<DataType::Cleared>(std::ifstream* filestream, const std::string& path) {
    if(!filestream->is_open()) {
        try { filestream->open(path); }
        catch (...) { throw ParserException("Couldn't open a file."); } 
    }
    cleared_data_path = path;
    std::string line;
    std::getline(*filestream, line);
    parse_csv_header(line);
    size_t line_idx = 0;
    for (line; std::getline(*filestream, line, '\n'); ++line_idx) {
    auto result = csv_stacker(line);
    flights.emplace_back(std::atoi(result[csv_header["AIR_TIME"]].c_str()),
                        result[csv_header["ORIGIN_CITY_NAME"]],
                        result[csv_header["DEST_CITY_NAME"]]);
    }
    filestream->close();
    flights.shrink_to_fit();

}


FlightParser::FlightParser(const std::string& path, DataType dtype) {
    std::ifstream* file = new std::ifstream(path, std::ios::in);
    int total_flights = scan_file(file, path);
    allocate(total_flights);
    if (DataType::Cleared == dtype) { parse<DataType::Cleared>(file, path); }
    else if (DataType::Dirty == dtype) { parse<DataType::Dirty>(file, path); }
    delete file;
}   


int FlightParser::scan_file(std::ifstream* filestream, const std::string& path) {
    if(!filestream->is_open()) {
        try { 
            filestream->open(path);
        }
        catch (...) {
            throw ParserException("Couldn't open a file.");
        } 
    }
    int lines = 0;
    char c;
    while (filestream->get(c)) {
        if (c == '\n') ++lines;
    }
    if (filestream->eof() && lines > 0) ++lines;
    std::cout << "Lines in scanned file: " << lines << "\n";
    filestream->close();
    return lines - 1;
}


void FlightParser::allocate(int sz) {
    if (sz <= 0) {
        throw ParserException("File ain't has data in it.");
    }
    try {
        flights.reserve(sz);
        std::cout << "Allocated vector of total flights: " << flights.capacity() << "\n";
    }
    catch(std::exception& e) {
        throw ParserException(e.what());
    }
}


std::vector<std::string> FlightParser::csv_stacker(const std::string& line) {
    CsvLineState state = CsvLineState::UnquotedField;
    std::vector<std::string> fields{""};
    size_t field_index = 0;
    for (char c: line) {
        switch(state) {
            case CsvLineState::UnquotedField: {
                switch(c) {
                    case ',': {
                        fields.push_back("");
                        ++field_index;
                        break;
                    }
                    case '"': {
                        state = CsvLineState::QuotedField;
                        break;
                    }
                    default: {
                        fields[field_index].push_back(c);
                        break;
                    }   
                }
                break;
            }
            case CsvLineState::QuotedField: {
                switch(c) {
                    case '"': {
                        state = CsvLineState::QuotedQuote;
                        break;
                    }
                    default: {
                        fields[field_index].push_back(c);
                        break;
                    }
                }
                break;
            }
            case CsvLineState::QuotedQuote: {
                switch(c) {
                    case ',': {
                        fields.push_back("");
                        ++field_index;
                        state = CsvLineState::UnquotedField;
                        break;
                    }
                    case '"': {
                        fields[field_index].push_back('"');
                        state = CsvLineState::QuotedField;
                        break;
                    }
                    default: {
                        state = CsvLineState::UnquotedField;
                    }
                }
                break;
            } 
        }
    }
    return fields;
}


void FlightParser::parse_csv_header(const std::string& header_line) {
    auto header_list = csv_stacker(header_line);
    for (size_t idx = 0; idx < header_list.size(); ++idx) {
        csv_header[header_list[idx]] = idx;
    }
}


const Flight& FlightParser::operator[](const size_t idx) const{
    return flights.at(idx);
}


bool FlightParser::check_data_line(std::vector<std::string>& flight_line, size_t line_idx) {
    if (flight_line[csv_header["AIR_TIME"]] == "" ||
        std::atoi(flight_line[csv_header["AIR_TIME"]].c_str()) <= 0) {
        // std::cout << "Bad air time for flight #" << line_idx << "\n";
        return false;
    }
    if (flight_line[csv_header["DEST_CITY_NAME"]] == "") {
        // std::cout << "Bad destination city name for flight #" << line_idx << "\n";
        return false;
    }
    if (flight_line[csv_header["ORIGIN_CITY_NAME"]] == "") {
        // std::cout << "Bad origin city name for flight #" << line_idx << "\n";
        return false;
    }
    if (flight_line[csv_header["ORIGIN_CITY_NAME"]] == flight_line[csv_header["DEST_CITY_NAME"]]) {
        // std::cout << "Origin city and dest city names are equal for flight #" << line_idx << "\n";
        return false;
    }
    return true;
}


void FlightParser::append_cleared_header(const std::string& source_path) {
    namespace fs = std::filesystem;
    fs::path p(source_path);
    p.replace_filename(p.replace_extension().filename().string() + "_cleared.csv");
    cleared_data_path = p.string();
    std::ofstream outfile(cleared_data_path, std::ios::out);
    if (!outfile.is_open()) { throw ParserException("Couldn't create file for cleared data."); }
    outfile << "AIR_TIME" << "," << "ORIGIN_CITY_NAME" << "," << "DEST_CITY_NAME\n";
    outfile.close();
}

void FlightParser::append_cleared_data_file() {
    std::ofstream outfile(cleared_data_path, std::ios_base::app);
    if (!outfile.is_open()) { throw ParserException("Couldn't open file for cleared data."); }

    const Flight& last_flight = flights.back();
    outfile << last_flight.air_time << ",\"" << last_flight.origin_city << "\",\"" << last_flight.dest_city << "\"\n";
    outfile.close();    
}   
