#include "crow_all.h"
#include <thread>
#include <atomic>
#include <iostream>
#include <string>

class PCCommunicator {
    float front_distance_sensor = -1;
    int move_command = -1;

    int get_direction_code(const std::string& direction) {
        if (direction == "front") {
            return 0;
        } else if (direction == "back") {
            return 1;
        } else if (direction == "left") {
            return 2;
        } else if (direction == "right") {
            return 3;
        } else {
            return -1;
        }
    }

public:
    PCCommunicator() : running(true) {
        std::cout << "Server on robot starts" << std::endl;
        web_server_thread = std::thread(&PCCommunicator::start_server, this);
    }

    int get_command() {
        return move_command;
    }

    ~PCCommunicator() {
        running = false;
        if (web_server_thread.joinable()) {
            web_server_thread.join();
        }
    }

private:
    std::thread web_server_thread;
    std::atomic<bool> running;

    void start_server() {
        crow::SimpleApp app;

        CROW_ROUTE(app, "/move/<string>")
        ([this](const std::string& direction) {
            move_command = get_direction_code(direction);
            return crow::response(200, "Move command sent");
        });

        CROW_ROUTE(app, "/distance")
        ([this]() {
            crow::json::wvalue distance;
            distance["front"] = front_distance_sensor;
            return distance;
        });

        app.port(5000).multithreaded().run();
    }
};