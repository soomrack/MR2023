// MESSAGE RANGEFINDER_CM support class

#pragma once

namespace mavlink {
namespace omegabot_manual_control {
namespace msg {

/**
 * @brief RANGEFINDER_CM message
 *
 * Rangefinder Data
 */
struct RANGEFINDER_CM : mavlink::Message {
    static constexpr msgid_t MSG_ID = 2;
    static constexpr size_t LENGTH = 5;
    static constexpr size_t MIN_LENGTH = 5;
    static constexpr uint8_t CRC_EXTRA = 205;
    static constexpr auto NAME = "RANGEFINDER_CM";


    char direction; /*<  w, a, s, d */
    float distance; /*<  Distance in centimeters */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  direction: " << +direction << std::endl;
        ss << "  distance: " << distance << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << distance;                      // offset: 0
        map << direction;                     // offset: 4
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> distance;                      // offset: 0
        map >> direction;                     // offset: 4
    }
};

} // namespace msg
} // namespace omegabot_manual_control
} // namespace mavlink
