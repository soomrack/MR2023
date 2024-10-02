#include "orange_bot_udp_client.hpp"

orange_bot_udp_client::orange_bot_udp_client(int client_p)
{
    client_port = client_p;
    std::cout << client_port << " - client_port " << std::endl;
}


orange_bot_udp_client::~orange_bot_udp_client()
{
    close(sockfd);
}


int orange_bot_udp_client::create_client_socket()
{
    // Создаем UDP-сокет
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }
    std::cerr << "Client socket created " << std::endl;

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);
    client_addr.sin_addr.s_addr = INADDR_ANY;

    // Привязываем сокет
    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        std::cerr << "Binding failed!" << std::endl;
        return -1;
    }
    std::cerr << "Client socket binded " << std::endl;
    return 0; 
}

void orange_bot_udp_client::receive_speed_from_server(int* left_speed, int* right_speed)
{
    int left, right;
    char comma;

    // Очищаем буфер перед получением данных
    memset(buffer, 0, sizeof(buffer));

    // Получаем данные от сервера с любого порта
    int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &server_addr_len);
    /*
    if (recv_len < 0) std::cerr << "Receive failed!" << std::endl;
    else std::cout << "Received " << recv_len << " bytes from " << inet_ntoa(sender_addr.sin_addr) << ":" << ntohs(sender_addr.sin_port) << std::endl;
    */
    //std::cout << buffer << "- buffer" << std::endl; // debug

    std::string speed_string(buffer);
    std::stringstream ss(speed_string);

    // Читаем первое число, запятую и второе число
    ss >> left >> comma >> right;

    // Проверяем, что запятая на месте, и парсинг прошел успешно
    if (ss && comma == ',')
    {
        *left_speed = left;
        *right_speed = right;
    }
    else
        std::cerr << "Error of parsing string: " << speed_string << std::endl;
}



void orange_bot_udp_client::receive_frame_from_server() 
{
    // Получаем размер изображения
    int img_size;
    recvfrom(sockfd, &img_size, sizeof(img_size), 0, (struct sockaddr*)&server_addr, &server_addr_len);

    // Получаем само изображение
    std::vector<uchar> buffer(img_size);
    recvfrom(sockfd, buffer.data(), img_size, 0, (struct sockaddr*)&server_addr, &server_addr_len);

    // Декодируем изображение
    frame = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (frame.empty()) {
        std::cerr << "Failed to decode image!" << std::endl;
    }
}
    


/*
int main() {
    orange_bot_udp_client client;
    int left, right;

    client.create_server_socket();
    client.connect_to_server();
    client.transmit_server_info();

    client.receive_server_data(&left, &right);
    std::cout << "left: " << left << "right: "<< right << std::endl;
    return 0;
}*/
