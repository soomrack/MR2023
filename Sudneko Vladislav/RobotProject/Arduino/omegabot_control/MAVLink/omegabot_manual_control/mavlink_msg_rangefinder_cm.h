#pragma once
// MESSAGE RANGEFINDER_CM PACKING

#define MAVLINK_MSG_ID_RANGEFINDER_CM 2


typedef struct __mavlink_rangefinder_cm_t {
 float distance; /*<  Distance in centimeters*/
 char direction; /*<  w, a, s, d*/
} mavlink_rangefinder_cm_t;

#define MAVLINK_MSG_ID_RANGEFINDER_CM_LEN 5
#define MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN 5
#define MAVLINK_MSG_ID_2_LEN 5
#define MAVLINK_MSG_ID_2_MIN_LEN 5

#define MAVLINK_MSG_ID_RANGEFINDER_CM_CRC 205
#define MAVLINK_MSG_ID_2_CRC 205



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_RANGEFINDER_CM { \
    2, \
    "RANGEFINDER_CM", \
    2, \
    {  { "direction", NULL, MAVLINK_TYPE_CHAR, 0, 4, offsetof(mavlink_rangefinder_cm_t, direction) }, \
         { "distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_rangefinder_cm_t, distance) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_RANGEFINDER_CM { \
    "RANGEFINDER_CM", \
    2, \
    {  { "direction", NULL, MAVLINK_TYPE_CHAR, 0, 4, offsetof(mavlink_rangefinder_cm_t, direction) }, \
         { "distance", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_rangefinder_cm_t, distance) }, \
         } \
}
#endif

/**
 * @brief Pack a rangefinder_cm message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param direction  w, a, s, d
 * @param distance  Distance in centimeters
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rangefinder_cm_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               char direction, float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RANGEFINDER_CM_LEN];
    _mav_put_float(buf, 0, distance);
    _mav_put_char(buf, 4, direction);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#else
    mavlink_rangefinder_cm_t packet;
    packet.distance = distance;
    packet.direction = direction;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RANGEFINDER_CM;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
}

/**
 * @brief Pack a rangefinder_cm message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param direction  w, a, s, d
 * @param distance  Distance in centimeters
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rangefinder_cm_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               char direction, float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RANGEFINDER_CM_LEN];
    _mav_put_float(buf, 0, distance);
    _mav_put_char(buf, 4, direction);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#else
    mavlink_rangefinder_cm_t packet;
    packet.distance = distance;
    packet.direction = direction;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RANGEFINDER_CM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#endif
}

/**
 * @brief Pack a rangefinder_cm message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param direction  w, a, s, d
 * @param distance  Distance in centimeters
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rangefinder_cm_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   char direction,float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RANGEFINDER_CM_LEN];
    _mav_put_float(buf, 0, distance);
    _mav_put_char(buf, 4, direction);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#else
    mavlink_rangefinder_cm_t packet;
    packet.distance = distance;
    packet.direction = direction;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_RANGEFINDER_CM;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
}

/**
 * @brief Encode a rangefinder_cm struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rangefinder_cm C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rangefinder_cm_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rangefinder_cm_t* rangefinder_cm)
{
    return mavlink_msg_rangefinder_cm_pack(system_id, component_id, msg, rangefinder_cm->direction, rangefinder_cm->distance);
}

/**
 * @brief Encode a rangefinder_cm struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rangefinder_cm C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rangefinder_cm_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_rangefinder_cm_t* rangefinder_cm)
{
    return mavlink_msg_rangefinder_cm_pack_chan(system_id, component_id, chan, msg, rangefinder_cm->direction, rangefinder_cm->distance);
}

/**
 * @brief Encode a rangefinder_cm struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param rangefinder_cm C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rangefinder_cm_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_rangefinder_cm_t* rangefinder_cm)
{
    return mavlink_msg_rangefinder_cm_pack_status(system_id, component_id, _status, msg,  rangefinder_cm->direction, rangefinder_cm->distance);
}

/**
 * @brief Send a rangefinder_cm message
 * @param chan MAVLink channel to send the message
 *
 * @param direction  w, a, s, d
 * @param distance  Distance in centimeters
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rangefinder_cm_send(mavlink_channel_t chan, char direction, float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_RANGEFINDER_CM_LEN];
    _mav_put_float(buf, 0, distance);
    _mav_put_char(buf, 4, direction);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RANGEFINDER_CM, buf, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#else
    mavlink_rangefinder_cm_t packet;
    packet.distance = distance;
    packet.direction = direction;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RANGEFINDER_CM, (const char *)&packet, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#endif
}

/**
 * @brief Send a rangefinder_cm message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_rangefinder_cm_send_struct(mavlink_channel_t chan, const mavlink_rangefinder_cm_t* rangefinder_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_rangefinder_cm_send(chan, rangefinder_cm->direction, rangefinder_cm->distance);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RANGEFINDER_CM, (const char *)rangefinder_cm, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#endif
}

#if MAVLINK_MSG_ID_RANGEFINDER_CM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_rangefinder_cm_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  char direction, float distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, distance);
    _mav_put_char(buf, 4, direction);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RANGEFINDER_CM, buf, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#else
    mavlink_rangefinder_cm_t *packet = (mavlink_rangefinder_cm_t *)msgbuf;
    packet->distance = distance;
    packet->direction = direction;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_RANGEFINDER_CM, (const char *)packet, MAVLINK_MSG_ID_RANGEFINDER_CM_MIN_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN, MAVLINK_MSG_ID_RANGEFINDER_CM_CRC);
#endif
}
#endif

#endif

// MESSAGE RANGEFINDER_CM UNPACKING


/**
 * @brief Get field direction from rangefinder_cm message
 *
 * @return  w, a, s, d
 */
static inline char mavlink_msg_rangefinder_cm_get_direction(const mavlink_message_t* msg)
{
    return _MAV_RETURN_char(msg,  4);
}

/**
 * @brief Get field distance from rangefinder_cm message
 *
 * @return  Distance in centimeters
 */
static inline float mavlink_msg_rangefinder_cm_get_distance(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a rangefinder_cm message into a struct
 *
 * @param msg The message to decode
 * @param rangefinder_cm C-struct to decode the message contents into
 */
static inline void mavlink_msg_rangefinder_cm_decode(const mavlink_message_t* msg, mavlink_rangefinder_cm_t* rangefinder_cm)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    rangefinder_cm->distance = mavlink_msg_rangefinder_cm_get_distance(msg);
    rangefinder_cm->direction = mavlink_msg_rangefinder_cm_get_direction(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_RANGEFINDER_CM_LEN? msg->len : MAVLINK_MSG_ID_RANGEFINDER_CM_LEN;
        memset(rangefinder_cm, 0, MAVLINK_MSG_ID_RANGEFINDER_CM_LEN);
    memcpy(rangefinder_cm, _MAV_PAYLOAD(msg), len);
#endif
}
