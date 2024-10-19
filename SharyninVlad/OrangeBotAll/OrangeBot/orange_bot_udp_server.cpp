#include "orange_bot_udp_server.hpp"

orange_bot_udp_server::orange_bot_udp_server(int client_p, int server_p, std::string clientip)
{
    client_port = client_p;
    server_port = server_p;
    client_ip = clientip;
    std::cout << client_port << " - client_port  " << server_port << " - server_port" << std::endl;
}

orange_bot_udp_server::~orange_bot_udp_server()
{
    close(sockfd);
}


int orange_bot_udp_server::create_server_socket()
{
    // Создаем UDP-сокет
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }
    std::cerr << "Server socket created " << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    // Привязываем сокет
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Binding failed!" << std::endl;
        return -1;
    }
    std::cerr << "Server socket binded " << std::endl;
    return 0;
}


int orange_bot_udp_server::set_client_address()
{
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);

    // Преобразуем строковый IP-адрес клиента в формат, понятный сокетам
    if (inet_pton(AF_INET, client_ip.c_str(), &client_addr.sin_addr) <= 0) {
        std::cerr << "Invalid client address!" << std::endl;
        return -1;
    }
    std::cerr << "Client socket set" << std::endl;
    return 0;
}


int orange_bot_udp_server::transmit_speed_to_client(int left, int right, int status, int IMG_WIDTH, int IMG_HEIGHT)
{
    std::string speed_string = std::to_string(left) + "," + std::to_string(right) + "," + std::to_string(status) + "," + std::to_string(IMG_WIDTH) + "," + std::to_string(IMG_HEIGHT); // Объединение чисел в строку
    sendto(sockfd, speed_string.c_str(), speed_string.size(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr)); //посылаем строку клиенту
    //std::cout << speed_string.c_str() << std::endl;
    return 0;
}


void orange_bot_udp_server::transmit_frame_to_client(cv::Mat frame)
{
    // Сжимаем кадр в JPEG
    std::vector<uchar> buffer;
    std::vector<int> compression_params = { cv::IMWRITE_JPEG_QUALITY, 50 };
    cv::imencode(".jpg", frame, buffer, compression_params);

    // Отправляем размер буфера
    int img_size = buffer.size();
    sendto(sockfd, &img_size, sizeof(img_size), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

    // Отправляем сам буфер
    sendto(sockfd, buffer.data(), img_size, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}


/*
int main() {
    orange_bot_udp_server server;

    server.create_server_socket();

    std::cout << "Waiting for client request..." << std::endl;
    server.reseive_client_info();

    server.send_seed_to_client(-100,200);

    std::cout << "Sent number to the client." << std::endl;

    return 0;
}*/