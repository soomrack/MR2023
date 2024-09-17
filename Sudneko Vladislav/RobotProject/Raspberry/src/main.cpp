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
        // Listen sensors data from Arduino and send to the GCS
        arduino_communicator.readFromArduino();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Listen command data from GCS and send to arduino
        arduino_communicator.writeToArduino(pc_communicator.get_command());
    }

    return 0;
}