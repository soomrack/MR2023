#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string> 
#include <iostream>
#include <sstream> 
#include <cstring>
#include <opencv2/opencv.hpp>

class orange_bot_udp_client
{
public:
    int client_port, server_port;
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    std::string server_ip;
public: 
    char buffer[16] = {0};
    cv::Mat frame;

public:
    orange_bot_udp_client(int client_p);
    ~orange_bot_udp_client();
    int create_client_socket();
    int connect_to_server();
    void transmit_server_info();
    void receive_speed_from_server(int* left_speed, int* right_speed);
    void receive_frame_from_server();
    int set_server_address();
};