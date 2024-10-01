#include <thread>
#include <chrono>

#include "PCCommunicator.hpp"
#include "ArduinoCommunicator.hpp"

// Consts
const bool run = true;

int main() {
    PCCommunicator pc_communicator;

    ArduinoCommunicator arduino_communicator("/dev/ttyUSB0", 9600); 

    while (run) {
        std::cout << "Read from Arduino" << std::endl;
        // Listen sensors data from Arduino and send to the GCS
        // &arduino_communicator.readFromArduino();


        // Listen command data from GCS and send to arduino
        std::cout << "Write to arduino" << std::endl;

        if (!pc_communicator.is_autopilot()) {
            arduino_communicator.writeToArduino(pc_communicator.get_command());
        } else {
            arduino_communicator.writeToArduino(pc_communicator.get_connection_error_code());
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));    
}

    return 0;
}
