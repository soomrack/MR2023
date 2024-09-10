/** @file
 *  @brief MAVLink comm protocol generated from omegabot_manual_control.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_OMEGABOT_MANUAL_CONTROL_H
#define MAVLINK_OMEGABOT_MANUAL_CONTROL_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_OMEGABOT_MANUAL_CONTROL.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_OMEGABOT_MANUAL_CONTROL_XML_HASH 8466184244231878805

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 55, 1, 1, 0, 0, 0}, {1, 197, 1, 1, 0, 0, 0}, {2, 205, 5, 5, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_OMEGABOT_MANUAL_CONTROL

// ENUM DEFINITIONS


/** @brief The system uses the state 0 to indicate correct operation, while any other value represents an error. */
#ifndef HAVE_ENUM_SYSTEM_STATUS
#define HAVE_ENUM_SYSTEM_STATUS
typedef enum SYSTEM_STATUS
{
   SYSTEM_STATUS_CORRECT=0, /* All system parts works well | */
   SYSTEM_STATUS_ENUM_END=1, /*  | */
} SYSTEM_STATUS;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 3
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_heartbeat.h"
#include "./mavlink_msg_move_command.h"
#include "./mavlink_msg_rangefinder_cm.h"

// base include



#if MAVLINK_OMEGABOT_MANUAL_CONTROL_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_MOVE_COMMAND, MAVLINK_MESSAGE_INFO_RANGEFINDER_CM}
# define MAVLINK_MESSAGE_NAMES {{ "HEARTBEAT", 0 }, { "MOVE_COMMAND", 1 }, { "RANGEFINDER_CM", 2 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_OMEGABOT_MANUAL_CONTROL_H
