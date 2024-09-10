#pragma once
// MESSAGE MOVE_COMMAND PACKING

#define MAVLINK_MSG_ID_MOVE_COMMAND 1


typedef struct __mavlink_move_command_t {
 char command; /*<  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)*/
} mavlink_move_command_t;

#define MAVLINK_MSG_ID_MOVE_COMMAND_LEN 1
#define MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN 1
#define MAVLINK_MSG_ID_1_LEN 1
#define MAVLINK_MSG_ID_1_MIN_LEN 1

#define MAVLINK_MSG_ID_MOVE_COMMAND_CRC 197
#define MAVLINK_MSG_ID_1_CRC 197



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOVE_COMMAND { \
    1, \
    "MOVE_COMMAND", \
    1, \
    {  { "command", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_move_command_t, command) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOVE_COMMAND { \
    "MOVE_COMMAND", \
    1, \
    {  { "command", NULL, MAVLINK_TYPE_CHAR, 0, 0, offsetof(mavlink_move_command_t, command) }, \
         } \
}
#endif

/**
 * @brief Pack a move_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param command  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_move_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               char command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOVE_COMMAND_LEN];
    _mav_put_char(buf, 0, command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#else
    mavlink_move_command_t packet;
    packet.command = command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOVE_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
}

/**
 * @brief Pack a move_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param command  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_move_command_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               char command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOVE_COMMAND_LEN];
    _mav_put_char(buf, 0, command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#else
    mavlink_move_command_t packet;
    packet.command = command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOVE_COMMAND;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#endif
}

/**
 * @brief Pack a move_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param command  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_move_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   char command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOVE_COMMAND_LEN];
    _mav_put_char(buf, 0, command);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#else
    mavlink_move_command_t packet;
    packet.command = command;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOVE_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
}

/**
 * @brief Encode a move_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param move_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_move_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_move_command_t* move_command)
{
    return mavlink_msg_move_command_pack(system_id, component_id, msg, move_command->command);
}

/**
 * @brief Encode a move_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param move_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_move_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_move_command_t* move_command)
{
    return mavlink_msg_move_command_pack_chan(system_id, component_id, chan, msg, move_command->command);
}

/**
 * @brief Encode a move_command struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param move_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_move_command_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_move_command_t* move_command)
{
    return mavlink_msg_move_command_pack_status(system_id, component_id, _status, msg,  move_command->command);
}

/**
 * @brief Send a move_command message
 * @param chan MAVLink channel to send the message
 *
 * @param command  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_move_command_send(mavlink_channel_t chan, char command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOVE_COMMAND_LEN];
    _mav_put_char(buf, 0, command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOVE_COMMAND, buf, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#else
    mavlink_move_command_t packet;
    packet.command = command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOVE_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#endif
}

/**
 * @brief Send a move_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_move_command_send_struct(mavlink_channel_t chan, const mavlink_move_command_t* move_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_move_command_send(chan, move_command->command);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOVE_COMMAND, (const char *)move_command, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOVE_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_move_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  char command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_char(buf, 0, command);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOVE_COMMAND, buf, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#else
    mavlink_move_command_t *packet = (mavlink_move_command_t *)msgbuf;
    packet->command = command;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOVE_COMMAND, (const char *)packet, MAVLINK_MSG_ID_MOVE_COMMAND_MIN_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_LEN, MAVLINK_MSG_ID_MOVE_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE MOVE_COMMAND UNPACKING


/**
 * @brief Get field command from move_command message
 *
 * @return  Move direction: w, a, s, d. Grab f (catch), e (release), o (up), l (down)
 */
static inline char mavlink_msg_move_command_get_command(const mavlink_message_t* msg)
{
    return _MAV_RETURN_char(msg,  0);
}

/**
 * @brief Decode a move_command message into a struct
 *
 * @param msg The message to decode
 * @param move_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_move_command_decode(const mavlink_message_t* msg, mavlink_move_command_t* move_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    move_command->command = mavlink_msg_move_command_get_command(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOVE_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_MOVE_COMMAND_LEN;
        memset(move_command, 0, MAVLINK_MSG_ID_MOVE_COMMAND_LEN);
    memcpy(move_command, _MAV_PAYLOAD(msg), len);
#endif
}
