// MESSAGE HEARTBEAT support class

#pragma once

namespace mavlink {
namespace omegabot_manual_control {
namespace msg {

/**
 * @brief HEARTBEAT message
 *
 * The heartbeat message shows that a system or component is present and responding. 
 */
struct HEARTBEAT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 0;
    static constexpr size_t LENGTH = 1;
    static constexpr size_t MIN_LENGTH = 1;
    static constexpr uint8_t CRC_EXTRA = 55;
    static constexpr auto NAME = "HEARTBEAT";


    uint8_t system_status; /*<  System status */


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
        ss << "  system_status: " << +system_status << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << system_status;                 // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> system_status;                 // offset: 0
    }
};

} // namespace msg
} // namespace omegabot_manual_control
} // namespace mavlink
