/** @file
 *	@brief MAVLink comm testsuite protocol generated from omegabot_manual_control.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <gtest/gtest.h>
#include "omegabot_manual_control.hpp"

#ifdef TEST_INTEROP
using namespace mavlink;
#undef MAVLINK_HELPER
#include "mavlink.h"
#endif


TEST(omegabot_manual_control, HEARTBEAT)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::omegabot_manual_control::msg::HEARTBEAT packet_in{};
    packet_in.system_status = 5;

    mavlink::omegabot_manual_control::msg::HEARTBEAT packet1{};
    mavlink::omegabot_manual_control::msg::HEARTBEAT packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.system_status, packet2.system_status);
}

#ifdef TEST_INTEROP
TEST(omegabot_manual_control_interop, HEARTBEAT)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_heartbeat_t packet_c {
         5
    };

    mavlink::omegabot_manual_control::msg::HEARTBEAT packet_in{};
    packet_in.system_status = 5;

    mavlink::omegabot_manual_control::msg::HEARTBEAT packet2{};

    mavlink_msg_heartbeat_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.system_status, packet2.system_status);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(omegabot_manual_control, MOVE_COMMAND)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::omegabot_manual_control::msg::MOVE_COMMAND packet_in{};
    packet_in.command = 'A';

    mavlink::omegabot_manual_control::msg::MOVE_COMMAND packet1{};
    mavlink::omegabot_manual_control::msg::MOVE_COMMAND packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.command, packet2.command);
}

#ifdef TEST_INTEROP
TEST(omegabot_manual_control_interop, MOVE_COMMAND)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_move_command_t packet_c {
         'A'
    };

    mavlink::omegabot_manual_control::msg::MOVE_COMMAND packet_in{};
    packet_in.command = 'A';

    mavlink::omegabot_manual_control::msg::MOVE_COMMAND packet2{};

    mavlink_msg_move_command_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.command, packet2.command);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif

TEST(omegabot_manual_control, RANGEFINDER_CM)
{
    mavlink::mavlink_message_t msg;
    mavlink::MsgMap map1(msg);
    mavlink::MsgMap map2(msg);

    mavlink::omegabot_manual_control::msg::RANGEFINDER_CM packet_in{};
    packet_in.direction = 'E';
    packet_in.distance = 17.0;

    mavlink::omegabot_manual_control::msg::RANGEFINDER_CM packet1{};
    mavlink::omegabot_manual_control::msg::RANGEFINDER_CM packet2{};

    packet1 = packet_in;

    //std::cout << packet1.to_yaml() << std::endl;

    packet1.serialize(map1);

    mavlink::mavlink_finalize_message(&msg, 1, 1, packet1.MIN_LENGTH, packet1.LENGTH, packet1.CRC_EXTRA);

    packet2.deserialize(map2);

    EXPECT_EQ(packet1.direction, packet2.direction);
    EXPECT_EQ(packet1.distance, packet2.distance);
}

#ifdef TEST_INTEROP
TEST(omegabot_manual_control_interop, RANGEFINDER_CM)
{
    mavlink_message_t msg;

    // to get nice print
    memset(&msg, 0, sizeof(msg));

    mavlink_rangefinder_cm_t packet_c {
         17.0, 'E'
    };

    mavlink::omegabot_manual_control::msg::RANGEFINDER_CM packet_in{};
    packet_in.direction = 'E';
    packet_in.distance = 17.0;

    mavlink::omegabot_manual_control::msg::RANGEFINDER_CM packet2{};

    mavlink_msg_rangefinder_cm_encode(1, 1, &msg, &packet_c);

    // simulate message-handling callback
    [&packet2](const mavlink_message_t *cmsg) {
        MsgMap map2(cmsg);

        packet2.deserialize(map2);
    } (&msg);

    EXPECT_EQ(packet_in.direction, packet2.direction);
    EXPECT_EQ(packet_in.distance, packet2.distance);

#ifdef PRINT_MSG
    PRINT_MSG(msg);
#endif
}
#endif
