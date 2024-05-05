/**
 * @file parser.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 05.05.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <boost/signals2.hpp>

#include <cstring>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using city = std::pair<size_t, std::string>;
using city_tour = std::pair<double, std::pair<city, city>>;

static const std::regex re(",");

class parser
{
public:
    parser(const std::string &path_);
    void parse();

private:
    size_t parse_cities(std::istream &is);

private:
    std::vector<city> cities;
    std::string path;
    boost::signals2::signal<void(std::vector<std::vector<double>> &)> parsed;
};

#endif // PARSER_HPP_INCLUDED
