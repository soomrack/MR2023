#include "crow_all.h"
#include <thread>
#include <atomic>
#include <iostream>
#include <string>

class PCCommunicator {
    float front_distance_sensor = -1;
public:
    PCCommunicator() : running(true) {
        std::cout << "Server on robot starts" << std::endl;
        web_server_thread = std::thread(&PCCommunicator::start_server, this);
    }

    void move(const std::string& direction) {
        std::cout << "Move command received: " << direction << std::endl;
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
            this->move(direction);
            std::string result =  "Move command " + direction + " executed.";
            return crow::response(200, result);
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