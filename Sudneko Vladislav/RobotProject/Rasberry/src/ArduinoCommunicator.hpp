#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

class ArduinoSerial {
public:
    ArduinoSerial(const std::string& port, unsigned int baud_rate)
        : io(), serial(io, port) {
        serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    }

    // Read distance data from Arduino
    void readFromArduino() {
        boost::asio::streambuf buf;
        while (true) {
            boost::asio::read_until(serial, buf, '\n');  // Read until newline
            std::istream input(&buf);
            std::string line;
            std::getline(input, line);
            if (!line.empty()) {
                std::cout << "Arduino: " << line << std::endl;
            }
        }
    }

    // Send command ID to Arduino
    void writeToArduino(int commandID) {
        std::string command = "PC: " + std::to_string(commandID) + "\n";
        boost::asio::write(serial, boost::asio::buffer(command));
    }

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
};