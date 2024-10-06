#ifndef PCCOMMUNICATOR
#define PCCOMMUNICATOR

#include "crow_all.h"
#include "TimeCounter.hpp"
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>

class PCCommunicator {
    float front_distance_sensor = -1;
    int move_command = -1;
    int connection_error_code = 400;
    TimeCounter counter;
    std::thread web_server_thread;
    std::thread heartbeat_thread;
    std::atomic<bool> running;
    uint16_t critical_time = 10; 
    bool autopilot = false;

    int get_direction_code(const std::string& direction) {
        if (direction == "forward") {
            return 22;
        } else if (direction == "back") {
            return 33;
        } else if (direction == "left") {
            return 44;
        } else if (direction == "right") {
            return 55;
        } else if (direction == "catch") {
            return 66;
        } else if (direction == "release") {
            return 77;
        } else if (direction == "up") {
            return 88;
        } else if (direction == "down") {
            return 99;
        } else if (direction == "stop") {
            return 111;
        } else if (direction == "forward_until_obstacle") {
            return 122;
        } else if (direction == "forward_rotate_and_back") {
            return 133;
        } else {
            return 135; // do nothing
        }
    }

    void heartbeat_handler() {
        while (running) {
            std::cout << "Heartbeat time is " << counter.getCounter() << std::endl;
            if (counter.getCounter() > critical_time) {
                autopilot = true;
            } else {
                std::cout << move_command << " - move command" << std::endl;
                autopilot = false;
            }   
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

public:
    PCCommunicator() : running(true) {
        std::cout << "Server on robot starts" << std::endl;
        web_server_thread = std::thread(&PCCommunicator::start_server, this);
        heartbeat_thread = std::thread(&PCCommunicator::heartbeat_handler, this);
    }


    int get_command() {
        return move_command;
    }

    bool is_autopilot() {
        return autopilot;
    }

    int get_connection_error_code() {
        return connection_error_code;
    }

    ~PCCommunicator() {
        running = false;
        if (web_server_thread.joinable()) {
            web_server_thread.join();
        }
    }

private:

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

        CROW_ROUTE(app, "/heartbeat")
        ([this]() {
            counter.start();
            counter.reset();
            return crow::response(200, "Heartbeat command");
        });

        app.port(5000).multithreaded().run();

    }
};

#endif // PCCOMMUNICATOR