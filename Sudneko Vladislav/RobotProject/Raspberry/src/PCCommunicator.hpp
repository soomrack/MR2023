#ifndef PCCOMMUNICATOR
#define PCCOMMUNICATOR

#include "crow_all.h"
#include "TimeCounter.hpp"
#include "VideoCapture.hpp
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>

class PCCommunicator {
    float front_distance_sensor = -1;
    float left_distance_sensor  = -1;
    int move_command = -1;
    int connection_error_code = 400;
    TimeCounter counter;
    std::thread web_server_thread;
    std::thread heartbeat_thread;
    std::atomic<bool> running;
    uint16_t critical_time = 10; 
    bool connection_lost = false;
    VideoCaptureHandler videoHandler;

    void setSensorsData(float frontSensor, float leftSensor) {
        if (frontSensor >= 0 && leftSensor >= 0) {
            front_distance_sensor = frontSensor;
            left_distance_sensor  = leftSensor;
        }
    }

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
        } else if (direction == "autopilot") {
            return 144;
        } else {
            return 135; // do nothing
        }
    }

    void heartbeat_handler() {
        while (running) {
            std::cout << "Heartbeat time is " << counter.getCounter() << std::endl;
            if (counter.getCounter() > critical_time) {
                connection_lost = true;
            } else {
                std::cout << move_command << " - move command" << std::endl;
                connection_lost = false;
            }   
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

public:
    PCCommunicator(const std::string& ip) : running(true), videoHandler(ip) {
        std::cout << "Server on robot starts" << std::endl;
        web_server_thread = std::thread(&PCCommunicator::start_server, this);
        heartbeat_thread = std::thread(&PCCommunicator::heartbeat_handler, this);
    }

    void set_sensor_data(int forward, int left) {
        front_distance_sensor = forward;
        left_distance_sensor  = left;
    }

    int get_command() {
        return move_command;
    }

    bool is_connection_lost() {
        return connection_lost;
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

        CROW_ROUTE(app, "/video/<string>")
        ([this](const std::string& operation) {
            if (operation == "start") {
                videoHandler.startVideoCapture();
                return crow::response(200, "Video capture started");
            } else if (operation == "stop") {
                videoHandler.stopVideoCapture();
                return crow::response(200, "Video capture stopped");
            }
            return crow::response(200, "Video command sent");
        });

        CROW_ROUTE(app, "/sensors")
        ([this]() {
            crow::json::wvalue sensors;
            sensors["forward_rangefinder"] = front_distance_sensor;
            sensors["left_rangefinder"] = left_distance_sensor;
            return sensors;
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