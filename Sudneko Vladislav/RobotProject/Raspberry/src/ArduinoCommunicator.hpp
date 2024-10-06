#ifndef ARDUINOCOMMUNICATOR
#define ARDUINOCOMMUNICATOR

#include <iostream>
#include <libserialport.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <stdexcept>

class ArduinoCommunicator {
public:
    ArduinoCommunicator(const std::string& port, int baud_rate) 
        : port_name(port), baud_rate(baud_rate), serial_port(nullptr) {
        connect();
    }

    ~ArduinoCommunicator() {
        disconnect();
    }

    void readFromArduino() {
        char buffer[128];
        while (true) {
            if (isConnected()) {
                int bytes_read = sp_nonblocking_read(serial_port, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';  // Null-terminate the string
                    std::string line(buffer);
                    if (!line.empty()) {
                        std::cout << "Arduino: " << line << std::endl;
                    }
                } else if (bytes_read == SP_ERR_TIMEOUT) {
                    std::cout << "Timeout read ffrom Arduino" << std::endl;
                }
            } else {
                std::cout << "Connection lost, attempting to reconnect..." << std::endl;
                reconnect();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // Send command ID to Arduino
    void writeToArduino(int commandID) {
        if (isConnected()) {
            std::string command = "PC: " + std::to_string(commandID) + "\n";
            sp_nonblocking_write(serial_port, command.c_str(), command.length());
        } else {
            std::cout << "Cannot send command, not connected to Arduino!" << std::endl;
        }
    }

private:
    struct sp_port* serial_port;
    std::string port_name;
    int baud_rate;

    void connect() {
        sp_return result = sp_get_port_by_name(port_name.c_str(), &serial_port);
        if (result != SP_OK) {
            throw std::runtime_error("Error finding the port!");
        }

        result = sp_open(serial_port, SP_MODE_READ_WRITE);
        if (result != SP_OK) {
            throw std::runtime_error("Error opening the port!");
        }

        result = sp_set_baudrate(serial_port, baud_rate);
        if (result != SP_OK) {
            throw std::runtime_error("Error setting baud rate!");
        }

        sp_set_bits(serial_port, 8);
        sp_set_parity(serial_port, SP_PARITY_NONE);
        sp_set_stopbits(serial_port, 1);
        sp_set_flowcontrol(serial_port, SP_FLOWCONTROL_NONE);
    }

    void disconnect() {
        if (serial_port) {
            sp_close(serial_port);
            sp_free_port(serial_port);
            serial_port = nullptr;
        }
    }

    bool isConnected() {
        return serial_port != nullptr;
    }

    void reconnect() {
        disconnect();
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
        try {
            connect(); 
            std::cout << "Reconnected to Arduino." << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Reconnect failed: " << e.what() << std::endl;
        }
    }
};

#endif // ARDUINOCOMMUNICATOR
