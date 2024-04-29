/**
 * @file query.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 24.03.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef QUERY_HPP_INCLUDED
#define QUERY_HPP_INCLUDED

#include <cstdint>
#include <iostream>
namespace Message
{

enum class Query : uint8_t
{
    StepperCompleted,
    ResponseDataRequest,
    Parked
};

enum class Instance : uint8_t
{
    // from host messages
    None = 0x00,
    Azimuth = 0xAA,
    Elevation = 0xBB,
    Both,
    ADS = 0xCC,
    Common = 0xDD,
    Error = 0xFA,
    END
};

enum class Status : uint32_t
{
    OK = 0,
    I2CError,
    USBError, // hard error
    StepperError,
    CommunicationError, // soft error
    UnAvailable
};
}; // namespace Message

inline std::ostream &operator<<(std::ostream &os, const Message::Instance &command)
{
    switch (command)
    {
    case Message::Instance::ADS:
        os << "ADS1115";
        break;
    case Message::Instance::Azimuth:
        os << "azimuth";
        break;
    case Message::Instance::Elevation:
        os << "elevation";
        break;
    case Message::Instance::Both:
        os << "azimuth and elevation";
        break;
    case Message::Instance::Common:
        os << "common";
        break;
    case Message::Instance::Error:
        os << "error";
        break;
    default:
        os << "other";
        break;
    }
    return os;
}

#endif // QUERY_HPP_INCLUDED
