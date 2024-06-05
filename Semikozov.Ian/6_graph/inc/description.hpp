/**
 * @file description.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 06.06.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DESCRIPTION_HPP_INCLUDED
#define DESCRIPTION_HPP_INCLUDED

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace desc
{

struct flight;

using sptr = std::shared_ptr<flight>;
using flight_v = std::vector<sptr>;

struct flight : std::enable_shared_from_this<flight>
{

    uint16_t origin_city_market_id;
    uint16_t dest_city_market_id;
    std::string origin_city;
    std::string dest_city;
    double air_time;
    uint16_t airline_id;
    std::string unique_carrier_name;
};

inline std::ostream &operator<<(std::ostream &os, const flight &f)
{
    os << "Flight from " << f.origin_city << " to " << f.dest_city << " cost " << f.air_time
       << " on airline " << f.airline_id;

    return os;
}
}; // namespace desc

#endif // DESCRIPTION_HPP_INCLUDED
