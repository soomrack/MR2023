#include <iostream>
#include <pigpio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 12345  // Порт для получения данных

int main() {
    // Инициализация pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Ошибка инициализации pigpio" << std::endl;
        return -1;
    }

    // Настройка сокета для приема данных по UDP
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        gpioTerminate();
        return -1;
    }

    // Настройка локального адреса для приема данных
    sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(SERVER_PORT);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (sockaddr*)&localAddr, sizeof(localAddr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        close(sock);
        gpioTerminate();
        return -1;
    }

    // Основной цикл: получение данных и вывод их в консоль
    while (true) {
        char buffer[1];
        sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);

        // Получаем данные по UDP
        int received = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddr, &addrLen);
        if (received > 0) {
            std::cout << "Получена команда: " << buffer[0] << std::endl;
        }
    }

    // Закрываем сокет и завершаем работу pigpio
    close(sock);
    gpioTerminate();
    return 0;
}
