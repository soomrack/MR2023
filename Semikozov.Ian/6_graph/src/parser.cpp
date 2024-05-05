#include "parser.hpp"

#include <boost/format.hpp>
#include <fstream>

parser::parser(const std::string &path_) : path{ path_ } {}

void parser::parse()
{
    boost::format fmt = boost::format{ "File %1% is not opened" };
    std::string cities_path = path + "cities.csv", tours_path = path + "cleared_data.csv";

    std::fstream cities_file{ cities_path, std::ios_base::in };

    if (!cities_file.is_open() || cities_file.bad())
    {
        throw std::runtime_error{ (fmt % cities_path).str() };
    }

    size_t size = this->parse_cities(cities_file);

    std::fstream tours_file(tours_path, std::ios_base::in);
    if (!tours_file.is_open()) { throw std::runtime_error{ (fmt % tours_path).str() }; }

    auto filling = [&, this](std::vector<double> &adj_row, std::string &city)
    {
        adj_row.reserve(size);
        std::string line;
        size_t pos{ 0 };
        while (std::getline(tours_file, line))
        {
            if ((pos = line.find(city)) == std::string::npos) { continue; }

            std::stringstream ss(line);
        }
        for (auto it : adj_row) {}
    };

    std::vector<std::vector<double>> adj;
    adj.reserve(size);
}

size_t parser::parse_cities(std::istream &is)
{
    std::string line;
    size_t cities_cnt{ 0 };

    while (std::getline(is, line))
    {
        std::string delimiter = ",\"";

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length() - 1);
            auto cp = std::make_pair(std::stoul(token), line);
            cities.push_back(cp);
        }
        cities_cnt++;
    }

    return cities_cnt;
}
