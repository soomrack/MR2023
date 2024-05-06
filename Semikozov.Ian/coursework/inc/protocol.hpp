/**
 * @file protocol.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 24.03.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef PROTOCOL_HPP_INCLUDED
#define PROTOCOL_HPP_INCLUDED

#include <stdint.h>

#include "commands.hpp"
#include "query.hpp"

namespace Message
{

using HeaderType = uint32_t;

struct Common
{
    static constexpr HeaderType kDefaultHeader{0xABCDEFFF};

    HeaderType header{kDefaultHeader};
    Instance instance;
    Status err;

    uint32_t timeStamp;
} __attribute__((__packed__));

struct ClientData
{
    Command command;
    float main[2];
    uint8_t common;
} __attribute__((__packed__));

struct ServerData
{
    Query query;
    float adcRawValue[4];

    float sensorAngles[2];
    float standAngles[2];

    float voltage[4];

    float pointOfCenterMass[2];
    float pointOfStandAngles[2];
} __attribute__((__packed__));

struct ServerPacket
{
    Common common;
    ServerData load;
} __attribute__((__packed__));

struct ClientPacket
{
    Common common;
    ClientData load;
} __attribute__((__packed__));

}; // namespace Message

#endif // PROTOCOL_HPP_INCLUDED
