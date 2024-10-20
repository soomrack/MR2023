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
    if (bind(sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        std::cerr << "Binding failed!" << std::endl;
        return -1;
    }
    std::cerr << "Client socket binded " << std::endl;
    return 0;
}

int orange_bot_udp_client::receive_speed_from_server(int* left_speed, int* right_speed, int* status_speed, int* IMG_WIDTH_SIZE, int* IMG_HEIGHT_SIZE)
{
    int left, right, status, IMG_WIDTH, IMG_HEIGHT;
    char comma1, comma2, comma3, comma4;

    // Очищаем буфер перед получением данных
    memset(buffer, 0, sizeof(buffer));

    // Получаем данные от сервера с любого порта
    int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_addr, &server_addr_len);

    if (recv_len < 0) return -1;

    /*
    if (recv_len < 0) std::cerr << "Receive failed!" << std::endl;
    else std::cout << "Received " << recv_len << " bytes from " << inet_ntoa(sender_addr.sin_addr) << ":" << ntohs(sender_addr.sin_port) << std::endl;
    */
    //std::cout << "buffer: " << buffer << std::endl; // debug

    std::string speed_string(buffer);
    std::stringstream ss(speed_string);

    // Читаем первое число, запятую и второе число
    ss >> left >> comma1 >> right >> comma2 >> status >> comma3 >> IMG_WIDTH >> comma4 >> IMG_HEIGHT;

    // Проверяем, что запятая на месте, и парсинг прошел успешно
    if (ss && comma1 == ',')
    {
        *left_speed = left;
        *right_speed = right;
        if (comma2 == ',')
            *status_speed = status;
        if (comma3 == ',')
            *IMG_WIDTH_SIZE = IMG_WIDTH;
        if (comma4 == ',')
            *IMG_HEIGHT_SIZE = IMG_HEIGHT;
    }
    else
        std::cerr << "Error of parsing string: " << speed_string << std::endl;
    return 0;
}



int orange_bot_udp_client::receive_frame_from_server()
{
    // Получаем размер изображения
    int img_size;
    recvfrom(sockfd, &img_size, sizeof(img_size), 0, (struct sockaddr*)&server_addr, &server_addr_len);
    //std::cerr << img_size << std::endl;

    if (img_size <= 0 || img_size > MAX_IMG_SIZE) {  // Установите разумный предел MAX_IMG_SIZE
        //std::cerr << "Invalid image size received: " << img_size << std::endl;
        return -1;
    }

    // Получаем само изображение
    std::vector<uchar> buffer(img_size);
    int recv_len = recvfrom(sockfd, buffer.data(), img_size, 0, (struct sockaddr*)&server_addr, &server_addr_len);

    if (recv_len < 0) {
        std::cerr << "Failed to receive image data!" << std::endl;
        return -1;
    }

    if (recv_len != img_size) {
        //std::cerr << "Incomplete image data received!" << std::endl;
        return -1;
    }

    if (buffer.size() != img_size) {
        std::cerr << "Buffer size mismatch!" << std::endl;
        return -1;
    }

    // Декодируем изображение
    frame = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (frame.empty()) {
        std::cerr << "Failed to decode image!" << std::endl;
        return -1;
    }
    return 1;
}



/*
int main() {
    orange_bot_camera cam(320, 240);

    client_v.create_client_socket();

    while (1){
        client_v.receive_frame_from_server();
        cam.frame = client_v.frame;
        cam.show_frame("PC");

        if (cv::waitKey(1) == 27) {  // Нажмите ESC для выхода
            break;
        }
        usleep(20000);
    }
}*/