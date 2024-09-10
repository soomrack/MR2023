#ifndef GCSCOMMINICATOR
#define GCSCOMMUNICATOR

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <atomic>
#include "Libs/MAVLink/omegabot_manual_control/mavlink.h"

enum CommandType {
    UP, DOWN, LEFT, RIGHT, CATCH, RELEASE, GRAB_UP, GRAB_DOWN, NOTHING
};

class GCSCommunicator {
private:
    mavlink_channel_t channel;
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    CommandType command = NOTHING;
    std::atomic<bool> running;
    std::thread receive_thread;
    std::thread heartbeat_thread;
    uint8_t system_status = 0; // OK

protected:
    void send_heartbeat() {
        while (true)
        {
            mavlink_message_t msg;

            mavlink_msg_heartbeat_pack(1, 1, &msg, system_status);

            uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
            uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

            sendto(sockfd, buffer, len, 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

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
            case 'f':       return CATCH;
            case 'e':       return RELEASE;
            case 'o':       return GRAB_UP;
            case 'l':       return GRAB_DOWN;
            default:        return NOTHING;
        }
    }


    void receive() {
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        socklen_t len = sizeof(client_addr);
        int n = recvfrom(sockfd, buffer, MAVLINK_MAX_PACKET_LEN, 0, (struct sockaddr*)&client_addr, &len);

        if (n > 0) {
            mavlink_message_t msg;
            mavlink_status_t status;

            for (int i = 0; i < n; i++) {
                if (mavlink_parse_char(channel, buffer[i], &msg, &status)) {
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
                        command = get_command_type(move_command.command);
                    }
                }
            }
        }
    }

    void receive_loop() {
        while (running) {
            receive();
        }
    }

public:
    GCSCommunicator(const std::string& ip, int recv_port, int send_port) 
        : channel(MAVLINK_COMM_0), running(true) {
        
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            std::cerr << "Failed to create socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(send_port);
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

        memset(&client_addr, 0, sizeof(client_addr));
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(recv_port);
        client_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (const struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
            std::cerr << "Bind failed" << std::endl;
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        receive_thread = std::thread(&GCSCommunicator::receive_loop, this);
        heartbeat_thread = std::thread(&GCSCommunicator::send_heartbeat, this);
    }

    void move(CommandType command) {
        mavlink_message_t msg;
        char direction;

        switch (command) {
            case UP:        direction = 'w'; break;
            case DOWN:      direction = 's'; break;
            case LEFT:      direction = 'a'; break;
            case RIGHT:     direction = 'd'; break;
            case CATCH:     direction = 'f'; break;
            case RELEASE:   direction = 'e'; break;
            case GRAB_UP:   direction = 'o'; break;
            case GRAB_DOWN: direction = 'l'; break;
        }

        mavlink_msg_move_command_pack(1, 1, &msg, direction);

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

        sendto(sockfd, buffer, len, 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

        std::cout << "Sent MOVE_COMMAND with direction: " << direction << std::endl;
    }

    void send_distance(char distance_direction, float distance) {
        mavlink_message_t msg;
        
        mavlink_msg_rangefinder_cm_pack(1, 1, &msg, distance_direction, distance);

        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

        sendto(sockfd, buffer, len, 0, (const struct sockaddr*)&server_addr, sizeof(server_addr));

        std::cout << "Sent RANGEFINDER_CM with direction: " << distance_direction << std::endl;
    }

    CommandType get_command() {
        return command;
    }

    ~GCSCommunicator() {
        running = false;
        if (receive_thread.joinable()) {
            receive_thread.join();
        }
        if (heartbeat_thread.joinable()) {
            heartbeat_thread.join();
        }
        close(sockfd);
    }
};

#endif //GCSCOMMUNICATOR