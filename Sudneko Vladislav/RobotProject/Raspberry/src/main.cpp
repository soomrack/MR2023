#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include "PCCommunicator.hpp"
#include "ArduinoCommunicator.hpp"
#include "ConsoleHistorySaver.hpp"

const bool run = true;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <IP_ADDRESS>" << std::endl;
        return 1;
    }

    std::string ip_address = argv[1]; 

    PCCommunicator pc_communicator(ip_address);
    ArduinoCommunicator arduino_communicator("/dev/ttyUSB0", 9600); 
    ConsoleHistorySaver historySaver("robot_log.txt");

    while (run) {
        // arduino_communicator.readFromArduino();

        if (!pc_communicator.is_connection_lost()) {
            arduino_communicator.writeToArduino(pc_communicator.get_command());
        } else {
            std::cout << "Connection lost" << std::endl;
            arduino_communicator.writeToArduino(pc_communicator.get_connection_error_code());
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));    
    }

    return 0;
}
