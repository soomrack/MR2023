#ifndef ARDUINOCOMMUNICATOR
#define ARDUINOCOMMUNICATOR

#include <iostream>
#include <libserialport.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <atomic>
#include "SensorData.hpp"

class ArduinoCommunicator {
public:
    ArduinoCommunicator(const std::string& port, int baud_rate) 
        : port_name(port), baud_rate(baud_rate), serial_port(nullptr), stop_thread(false) {
        connect();
        startReadingThread();  // Start reading in a separate thread
    }

    ~ArduinoCommunicator() {
        stop_thread = true;  // Signal the thread to stop
        if (read_thread.joinable()) {
            read_thread.join();  // Wait for the thread to finish
        }
        disconnect();
    }

    std::tuple<int, int> get_sensor_data() {
        return SensorData::getValues();
    }

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
    std::thread read_thread;  // Thread for reading from Arduino
    std::atomic<bool> stop_thread;  // Flag to stop the thread

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

    void parseAndStoreData(const std::string& data) {
        // Example input: "Arduino: 2;45"
        if (data.find("Arduino: ") == 0) {
            std::cout << "Get data from Arduino: " << data << std::endl;
            std::stringstream ss(data.substr(9));  // Skip "Arduino: "
            int values[2];
            char delimiter;

            ss >> values[0] >> delimiter >> values[1];

            if (delimiter == ';') {
                SensorData::setValues(values[0], values[1]);
                std::cout << "Data updated - Forward: " << values[0] << ", Left: " << values[1] << std::endl;
            } else {
                std::cout << "Invalid data format received: " << data << std::endl;
            }
        }
    }

    void readFromArduino() {
        char buffer[128];
        while (!stop_thread) {
            if (isConnected()) {
                int bytes_read = sp_nonblocking_read(serial_port, buffer, sizeof(buffer) - 1);
                if (bytes_read > 0) {
                    buffer[bytes_read] = '\0';  
                    std::string line(buffer);
                    if (!line.empty()) {
                        std::cout << line << " - line" << std::endl;
                        parseAndStoreData(line);
                    }
                }
            } else {
                std::cout << "Connection lost, attempting to reconnect..." << std::endl;
                reconnect();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void startReadingThread() {
        read_thread = std::thread(&ArduinoCommunicator::readFromArduino, this);
    }
};

#endif // ARDUINOCOMMUNICATOR
