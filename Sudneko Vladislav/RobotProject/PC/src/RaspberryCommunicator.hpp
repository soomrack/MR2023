#ifndef RASPBERRYCOMMUNICATOR
#define RASPBERRYCOMMUNICATOR

#include "HTTPRequester.hpp"
#include "PingService.hpp"
#include "json.hpp"
#include <sstream>

class RaspberryCommunicator {
    HTTPRequester requester;
    PingService pingService;
    
public:
    RaspberryCommunicator(std::string raspberryAddress) : 
        requester(raspberryAddress), pingService(raspberryAddress) {};

    void sendMoveCommand(std::string command) noexcept {
        std::string request = "/move/" + command;
        requester.send_get_request(request);
    }

    void sendVideoCommand(std::string command) noexcept {
        std::string request = "/video/" + command;
        requester.send_get_request(request);
    }

    void sendHeartbeat() noexcept {
        std::string request = "/heartbeat"; 
        requester.send_get_request(request);
    }

    std::string getSensorsInfo() {
        std::string sensors_response = requester.send_get_request("/sensors");
        try {
            auto json_data = nlohmann::json::parse(sensors_response);

            std::stringstream text;
            text << "forward rangefinder = " << json_data["forward_rangefinder"].get<int>()
                 << ", humidity sensor = " << json_data["left_rangefinder"].get<int>();
                // << ", ping = " << pingService.getPingTime();

            return text.str();
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            return "Error in JSON parsing";
        }
    }
};

#endif // RASPBERRYCOMMUNICATOR
