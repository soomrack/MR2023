#pragma once
#include <iostream>
#include <libserialport.h>
#include <cstring>
#include <thread>
#include <chrono>

class ArduinoCommunicator {
public:
    ArduinoCommunicator(const std::string& port, int baud_rate) {
        // Open the serial port
        sp_return result = sp_get_port_by_name(port.c_str(), &serial_port);
        if (result != SP_OK) {
            throw std::runtime_error("Error finding the port!");
        }

        result = sp_open(serial_port, SP_MODE_READ_WRITE);
        if (result != SP_OK) {
            throw std::runtime_error("Error opening the port!");
        }

        // Set the baud rate
        result = sp_set_baudrate(serial_port, baud_rate);
        if (result != SP_OK) {
            throw std::runtime_error("Error setting baud rate!");
        }

        // Set other serial port parameters
        sp_set_bits(serial_port, 8);
        sp_set_parity(serial_port, SP_PARITY_NONE);
        sp_set_stopbits(serial_port, 1);
        sp_set_flowcontrol(serial_port, SP_FLOWCONTROL_NONE);
    }

    ~ArduinoCommunicator() {
        sp_close(serial_port);
        sp_free_port(serial_port);
    }

    // Read distance data from Arduino
    void readFromArduino() {
        char buffer[128];
        while (true) {
            int bytes_read = sp_nonblocking_read(serial_port, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';  // Null-terminate the string
                std::string line(buffer);
                if (!line.empty()) {
                    std::cout << "Arduino: " << line << std::endl;
                }
            }
        }
    }

    // Send command ID to Arduino
    void writeToArduino(int commandID) {
        std::string command = "PC: " + std::to_string(commandID) + "\n";
        sp_nonblocking_write(serial_port, command.c_str(), command.length());
    }

private:
    struct sp_port* serial_port;
};