#ifndef RASPBERRYCOMMUNICATOR
#define RASPBERRYCOMMUNICATOR

#include "HTTPRequester.hpp"
#include "json.hpp"

class RaspberryCommunicator {
    HTTPRequester requester;
public:
    RaspberryCommunicator(std::string raspberry_address) : requester(raspberry_address) {};

    void sendCommand(std::string command) noexcept {
        std::string request = "/move/" + command;
        requester.send_get_request(request);
    }

    void sendHeartbeat() noexcept {
        std::string request = "/heartbeat";
        requester.send_get_request(request);
    }

    float getDistance() {
        std::string distance_response = requester.send_get_request("/distance");
        try {
            auto json_data = nlohmann::json::parse(distance_response);
            return json_data["front"].get<float>();
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            return -1.0f;
        }
    }
};

#endif // RASPBERRYCOMMUNICATOR