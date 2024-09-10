#ifndef ARDUINOCOMMUNICATOR
#define ARDUINOCOMMUNICATOR

#include <iostream>
#include <wiringPiI2C.h>
#include <thread>
#include <atomic>
#include <chrono>
#include "Libs/MAVLink/omegabot_manual_control/mavlink.h"

enum CommandType {
    UP, DOWN, LEFT, RIGHT, GRASP, RELEASE, GRAB_UP, GRAB_DOWN, NOTHING
};

class ArduinoCommunicator {
private:
    int i2c_fd;
    int arduino_address;
    CommandType command = NOTHING;
    float distance = -1;
    char distance_direction = '\0';
    std::atomic<bool> running;
    std::thread receive_thread;
    std::thread heartbeat_thread;
    uint8_t system_status = SYSTEM_STATUS_CORRECT;

protected:
    void send_heartbeat() {
        while (true) {
            mavlink_message_t msg;

            mavlink_msg_heartbeat_pack(1, 1, &msg, system_status);

            uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
            uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

            // Send the heartbeat over I2C to Arduino
            for (uint16_t i = 0; i < len; ++i) {
                wiringPiI2CWrite(i2c_fd, buffer[i]);
            }

            std::cout << "Sent HEARTBEAT with status: " << std::to_string(system_status) << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    CommandType get_command_type(char command) {
        switch (command) {
            case 'w':       return UP;
            case 's':       return DOWN;
            case 'a':       return LEFT;
            case 'd':       return RIGHT;
            case 'f':       return GRASP;
            case 'e':       return RELEASE;
            case 'o':       return GRAB_UP;
            case 'l':       return GRAB_DOWN;
            default:        return NOTHING;
        }
    }

    void receive() {
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        int n = 0;
        
        // Receive data over I2C from Arduino
        while (n < MAVLINK_MAX_PACKET_LEN) {
            int data = wiringPiI2CRead(i2c_fd);
            if (data < 0) {
                std::cerr << "Failed to receive data from Arduino" << std::endl;
                return;
            }
            buffer[n++] = data;
        }

        mavlink_message_t msg;
        mavlink_status_t status;

        for (int i = 0; i < n; i++) {
            if (mavlink_parse_char(MAVLINK_COMM_0, buffer[i], &msg, &status)) {
                if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
                    mavlink_heartbeat_t heartbeat;
                    mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                    if (heartbeat.system_status != SYSTEM_STATUS_CORRECT) {
                        std::cout << "Received HEARTBEAT. Problems with system, status: " << heartbeat.system_status << std::endl;
                    } else {
                        std::cout << "Received HEARTBEAT. Status: OK" << std::endl;
                    }
                } else if (msg.msgid == MAVLINK_MSG_ID_MOVE_COMMAND) {
                    mavlink_move_command_t move_command;
                    mavlink_msg_move_command_decode(&msg, &move_command);
                    std::cout << "Received MOVE_COMMAND with direction: " << move_command.command << std::endl;
                    command = move_command.command;
                } else if (msg.msgid == MAVLINK_MSG_ID_RANGEFINDER_CM) {
                    mavlink_rangefinder_cm_t rangefinder_cm_t;
                    mavlink_msg_rangefinder_cm_decode(&msg, &rangefinder_cm_t);
                    std::cout << "Received RANGEFINDER_CM with direction: " << rangefinder_cm_t.direction << std::endl;
                    distance = rangefinder_cm_t.distance;
                    distance_direction = rangefinder_cm_t.direction;
                }
            }
        }
    }

public:
    ArduinoCommunicator(int arduino_address) 
        : arduino_address(arduino_address), running(true) {

        // Initialize I2C communication with Arduino
        i2c_fd = wiringPiI2CSetup(arduino_address);
        if (i2c_fd < 0) {
            std::cerr << "Failed to initiate I2C communication" << std::endl;
            exit(EXIT_FAILURE);
        }

        receive_thread = std::thread(&ArduinoCommunicator::receive_loop, this);
        heartbeat_thread = std::thread(&ArduinoCommunicator::send_heartbeat, this);
    }

    void move(CommandType command) {
        mavlink_message_t msg;
        char direction;

        switch (command) {
            case UP:        direction = 'w'; break;
            case DOWN:      direction = 's'; break;
            case LEFT:      direction = 'a'; break;
            case RIGHT:     direction = 'd'; break;
            case GRASP:     direction = 'f'; break;
            case RELEASE:   direction = 'e'; break;
            case GRAB_UP:   direction = 'o'; break;
            case GRAB_DOWN: direction = 'l'; break;
        }

        mavlink_msg_move_command_pack(1, 1, &msg, direction);

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

        // Send the move command over I2C to Arduino
        for (uint16_t i = 0; i < len; ++i) {
            wiringPiI2CWrite(i2c_fd, buffer[i]);
        }

        std::cout << "Sent MOVE_COMMAND with direction: " << direction << std::endl;
    }

    void send_distance() {
        mavlink_message_t msg;
        
        mavlink_msg_rangefinder_cm_pack(1, 1, &msg, distance_direction, distance);

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

        // Send the distance data over I2C to Arduino
        for (uint16_t i = 0; i < len; ++i) {
            wiringPiI2CWrite(i2c_fd, buffer[i]);
        }

        std::cout << "Sent RANGEFINDER_CM with direction: " << distance_direction << std::endl;
    }

    void set_distance(char orientation, float distance_cm) {
        distance_direction = orientation;
        distance = distance_cm;
    }

    void receive_loop() {
        while (running) {
            receive();
        }
    }

    CommandType get_command() {
        return command;
    }

    char get_distance_direction() {
        return distance_direction;
    }

    float get_distance() {
        return distance;
    }

    ~ArduinoCommunicator() {
        running = false;
        if (receive_thread.joinable()) {
            receive_thread.join();
        }
        if (heartbeat_thread.joinable()) {
            heartbeat_thread.join();
        }
    }
};

#endif // ARDUINOCOMMUNICATOR
