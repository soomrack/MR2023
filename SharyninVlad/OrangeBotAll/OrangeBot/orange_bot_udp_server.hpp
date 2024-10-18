#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>

class orange_bot_udp_server
{
public:
    int client_port, server_port;
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    std::string client_ip;
public:
    orange_bot_udp_server(int client_p, int server_p, std::string clientip);
    ~orange_bot_udp_server();
    int create_server_socket();
    int transmit_speed_to_client(int left, int right, int status);
    void transmit_frame_to_client(cv::Mat frame);
    int set_client_address();
};