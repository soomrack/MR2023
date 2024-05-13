#include <iostream>
#include "parser.hpp"
#include "sstream"

using namespace DjikstraAirlanesParser;

FlightParser::FlightParser(const std::string& path) {
    std::ifstream* file = new std::ifstream(path, std::ios::in);
    int total_flights = scan_file(file, path);
    allocate(total_flights);
    parse(file, path);
    delete file;
}   


int FlightParser::scan_file(std::ifstream* filestream, const std::string& path) {
    if(!filestream->is_open()) {
        try { 
            filestream->open(path);
        }
        catch (...) {
            throw std::runtime_error("Couldn't open a file.");
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
        throw std::runtime_error("File ain't has data in it.");
    }
    try {
        flights.reserve(sz);
        std::cout << "Allocated vector of total flights: " << flights.capacity() << "\n";
    }
    catch(std::exception& e) {
        throw std::runtime_error(e.what());
    }
}


void FlightParser::parse(std::ifstream* filestream, const std::string& path) {
    if(!filestream->is_open()) {
        try { 
            filestream->open(path);
        }
        catch (...) {
            throw std::runtime_error("Couldn't open a file.");
        } 
    }

    std::string line;
    std::getline(*filestream, line);
    parse_header(line);
    for (line; std::getline(*filestream, line, '\n');) {
        auto result = csv_stacker(line);
        flights.emplace_back(std::atoi(result[csv_header["AIR_TIME"]].c_str()),
                            result[csv_header["ORIGIN_CITY_NAME"]],
                            result[csv_header["DEST_CITY_NAME"]]);
    }
    filestream->close();
}


std::vector<std::string> FlightParser::csv_stacker(const std::string line) {
    CsvLineStatus status = CsvLineStatus::UnquotedField;
    std::vector<std::string> fields{""};
    size_t field_index = 0;
    for (char c: line) {
        switch(status) {
            case CsvLineStatus::UnquotedField: {
                switch(c) {
                    case ',': {
                        fields.push_back("");
                        ++field_index;
                        break;
                    }
                    case '"': {
                        status = CsvLineStatus::QuotedField;
                        break;
                    }
                    default: {
                        fields[field_index].push_back(c);
                        break;
                    }   
                }
                break;
            }
            case CsvLineStatus::QuotedField: {
                switch(c) {
                    case '"': {
                        status = CsvLineStatus::QuotedQuote;
                        break;
                    }
                    default: {
                        fields[field_index].push_back(c);
                        break;
                    }
                }
                break;
            }
            case CsvLineStatus::QuotedQuote: {
                switch(c) {
                    case ',': {
                        fields.push_back("");
                        ++field_index;
                        status = CsvLineStatus::UnquotedField;
                        break;
                    }
                    case '"': {
                        fields[field_index].push_back('"');
                        status = CsvLineStatus::QuotedField;
                        break;
                    }
                    default: {
                        status = CsvLineStatus::UnquotedField;
                    }
                }
                break;
            } 
        }
    }
    return fields;
}


void FlightParser::parse_header(const std::string& header_line) {
    auto header_list = csv_stacker(header_line);
    header_list[0] = "IDX";
    for (size_t idx = 0; idx < header_list.size(); ++idx) {
        csv_header[header_list[idx]] = idx;
    }
}


const Flight& FlightParser::operator[](const size_t idx) const{
    return flights.at(idx);
}


