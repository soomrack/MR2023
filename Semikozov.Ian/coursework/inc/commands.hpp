/**
 * @file commands.hpp
 * @author Semikozov Ian (semikozov.yal@yandex.ru)
 * @brief
 * @version 0.1
 * @date 24.03.2024
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef COMMANDS_HPP_INCLUDED
#define COMMANDS_HPP_INCLUDED

#include <cstdint>
#include <iostream>

namespace Commands
{

enum class ADC : uint8_t
{
    None = 0x01,

    SetFSR,
    SetSPS,
    SetMode,
    SetMux,

    GetFSR,
    GetSPS,
    GetMode,
    GetMux,

    SetRef, //!< change channel for channel, or channel for GND

    ReadMux,
    ReadAllMuxs,

    END //! NEEDED
};

enum class Stepper : uint8_t
{
    None = 0x21,

    DecreaseAngle,
    IncreaseAngle,

    ForceSetAngle, //!< set without move, needed for moving stepper on 90 degrees after park
    SetAngle,
    SetAngles,
    SetSteps,

    SetRPM,
    Park,

    END //! NEEDED
};

enum class Common : uint8_t
{
    None = 0x41,

    GetCalibration,
    GetData,
    GetNoise,

    END //! NEEDED
};
}; // namespace Commands

inline std::ostream &operator<<(std::ostream &os, const Commands::Common &command)
{
    switch (command)
    {
    case Commands::Common::GetCalibration:
        os << "to get calibration data";
        break;
    case Commands::Common::GetData:
        os << "to request data";
        break;
    case Commands::Common::GetNoise:
        os << "to get noise on angle";
        break;
    default:
        os << "other";
        break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const Commands::Stepper &command)
{
    switch (command)
    {
    case Commands::Stepper::DecreaseAngle:
        os << "to decrease angle";
        break;
    case Commands::Stepper::IncreaseAngle:
        os << "to increase angle";
        break;
    case Commands::Stepper::SetAngle:
        os << "to set angle";
        break;
    case Commands::Stepper::Park:
        os << "to park stepper";
        break;
    default:
        os << "other";
        break;
    }
    return os;
}

inline std::ostream &operator<<(std::ostream &os, const Commands::ADC &command)
{
    switch (command)
    {
    case Commands::ADC::SetFSR:
        os << "to set full scale range";
        break;
    case Commands::ADC::SetMode:
        os << "to set mode";
        break;
    case Commands::ADC::ReadMux:
        os << "to read multiplexer";
        break;
    case Commands::ADC::ReadAllMuxs:
        os << "to read all multiplexers";
        break;

    default:
        os << "other";
        break;
    }
    return os;
}

// only from host
struct Command
{
    /* Range: 0x01 - 0x20 */
    Commands::Stepper stepperCommand;
    /* Range: 0x21 - 0x40 */
    Commands::ADC adsCommand;
    /* Range: 0x41 - 0xFF */
    Commands::Common commonCommand;
};

#endif // COMMANDS_HPP_INCLUDED
