/** @file
 *	@brief MAVLink comm protocol generated from omegabot_manual_control.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#ifndef MAVLINK_STX
#define MAVLINK_STX 253
#endif

#include "../message.hpp"

namespace mavlink {
namespace omegabot_manual_control {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (through @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 3> MESSAGE_ENTRIES {{ {0, 55, 1, 1, 0, 0, 0}, {1, 197, 1, 1, 0, 0, 0}, {2, 205, 5, 5, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 3;


// ENUM DEFINITIONS


/** @brief The system uses the state 0 to indicate correct operation, while any other value represents an error. */
enum class SYSTEM_STATUS : uint8_t
{
    CORRECT=0, /* All system parts works well | */
};

//! SYSTEM_STATUS ENUM_END
constexpr auto SYSTEM_STATUS_ENUM_END = 1;


} // namespace omegabot_manual_control
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.hpp"
#include "./mavlink_msg_move_command.hpp"
#include "./mavlink_msg_rangefinder_cm.hpp"

// base include

