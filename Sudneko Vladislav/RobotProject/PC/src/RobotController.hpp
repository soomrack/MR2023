#ifndef ROBOTCONTROLLER
#define ROBOTCONTROLLER

#include "RaspberryCommunicator.hpp"
#include <iostream>
#include <string>

class RobotController {
private:
    RaspberryCommunicator communicator;
    std::string robotInfo;
    std::string robotIp;

public:
    RobotController(const std::string& robot_host)
        : communicator(robot_host) {} 

    void moveForward() {
        communicator.sendMoveCommand("forward");
        std::cout << "Moving forward" << std::endl;
    }

    void moveBackward() {
        communicator.sendMoveCommand("back");
        std::cout << "Moving backward" << std::endl;
    }

    void moveLeft() {
        communicator.sendMoveCommand("left");
        std::cout << "Moving left" << std::endl;
    }

    void moveRight() {
        communicator.sendMoveCommand("right");
        std::cout << "Moving right" << std::endl;
    }

    void grabCatch() {
        communicator.sendMoveCommand("catch");
        std::cout << "Catching" << std::endl;
    }

    void grabRelease() {
        communicator.sendMoveCommand("release");
        std::cout << "Releasing" << std::endl;
    }

    void grabUp() {
        communicator.sendMoveCommand("up");
        std::cout << "Grab Up" << std::endl;
    }

    void grabDown() {
        communicator.sendMoveCommand("down");
        std::cout << "Grab Down" << std::endl;
    }

    void forwardUntilObstacle() {
        communicator.sendMoveCommand("forward_until_obstacle");
        std::cout << "Forward until obstacle" << std::endl;
    }

    void forwardRotateAndBack() {
        communicator.sendMoveCommand("forward_rotate_and_back");
        std::cout << "Forward, rotate and back" << std::endl;
    }

    void autopilot() {
        communicator.sendMoveCommand("autopilot");
        std::cout << "Start autopilot" << std::endl;
    }

    void startShootingVideo() {
        communicator.sendVideoCommand("start");
        std::cout << "Start video recording" << std::endl;
    }

    void stopShootingVideo() {
        communicator.sendVideoCommand("stop");
        std::cout << "Stop video recording" << std::endl;
    }

    void stop() {
        communicator.sendMoveCommand("stop");
        std::cout << "Stop robot" << std::endl;
    }

    void sendHeartbeat() {
        communicator.sendHeartbeat();
        std::cout << "HeartBeat sent" << std::endl;
    }

    std::string getInfo() {
        robotInfo = communicator.getSensorsInfo();
        return robotInfo;
    }
};

#endif // ROBOTCONTROLLER