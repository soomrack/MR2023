#ifndef ROBOTCONTROLLER
#define ROBOTCONTROLLER

#include "GCSCommunicator.hpp"
#include <iostream>

class RobotController {
private:
    GCSCommunicator communicator;

public:
    RobotController(const std::string& ip, int recv_port, int send_port)
        : communicator(ip, recv_port, send_port) { } 

    void moveForward() {
        communicator.move(UP);
        std::cout << "Moving forward" << std::endl;
    }

    void moveBackward() {
        communicator.move(DOWN);
        std::cout << "Moving backward" << std::endl;
    }

    void moveLeft() {
        communicator.move(LEFT);
        std::cout << "Moving left" << std::endl;
    }

    void moveRight() {
        communicator.move(RIGHT);
        std::cout << "Moving right" << std::endl;
    }

    void grabCatch() {
        communicator.move(CATCH);
        std::cout << "Catching" << std::endl;
    }

    void grabRelease() {
        communicator.move(RELEASE);
        std::cout << "Releasing" << std::endl;
    }

    void grabUp() {
        communicator.move(UP);
        std::cout << "Grab Up" << std::endl;
    }

    void grabDown() {
        communicator.move(DOWN);
        std::cout << "Grab Down" << std::endl;
    }
};

#endif // ROBOTCONTROLLER