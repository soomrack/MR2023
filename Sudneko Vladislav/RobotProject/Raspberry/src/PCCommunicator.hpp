#include "crow_all.h"
#include "TimeCounter.hpp"
#include <thread>
#include <atomic>
#include <iostream>
#include <string>

class PCCommunicator {
    float front_distance_sensor = -1;
    int move_command = -1;
    TimeCounter counter;


    int get_direction_code(const std::string& direction) {
        if (direction == "forward") {
            return 22;
        } else if (direction == "back") {
            return 33;
        } else if (direction == "left") {
            return 44;
        } else if (direction == "right") {
            return 55;
        } else {
            return 135;
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
            distance["forward"] = front_distance_sensor;
            return distance;
        });

        CROW_ROUTE(app, "/heatbeat")
        ([this]() {
            counter.start();
            counter.reset();
            return crow::response(200, "Heartbeat command");
        });

        app.port(5000).multithreaded().run();

    }
};
