#ifndef ROBOTCONTROLLER
#define ROBOTCONTROLLER

#include "RaspberryCommunicator.hpp"
#include <iostream>

class RobotController {
private:
    RaspberryCommunicator communicator;

public:
    RobotController(const std::string& robot_host)
        : communicator(robot_host) { } 

    void moveForward() {
        communicator.sendCommand("/forward");
        std::cout << "Moving forward" << std::endl;
    }

    void moveBackward() {
        communicator.sendCommand("/down");
        std::cout << "Moving backward" << std::endl;
    }

    void moveLeft() {
        communicator.sendCommand("/left");
        std::cout << "Moving left" << std::endl;
    }

    void moveRight() {
        communicator.sendCommand("/right");
        std::cout << "Moving right" << std::endl;
    }

    void grabCatch() {
        communicator.sendCommand("/catch");
        std::cout << "Catching" << std::endl;
    }

    void grabRelease() {
        communicator.sendCommand("/release");
        std::cout << "Releasing" << std::endl;
    }

    void grabUp() {
        communicator.sendCommand("/up");
        std::cout << "Grab Up" << std::endl;
    }

    void grabDown() {
        communicator.sendCommand("/down");
        std::cout << "Grab Down" << std::endl;
    }
};

#endif // ROBOTCONTROLLER