#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <conio.h>  // Для работы с функцией _kbhit() и _getch()
#include <thread>
#include <vector>
#include <opencv2/opencv.hpp>  // OpenCV для отображения видео

#pragma comment(lib, "ws2_32.lib")  // Подключение библиотеки Winsock

#define SERVER_IP "192.168.110.232"  // IP адрес Raspberry
#define SERVER_PORT 12345         // Порт для передачи команд
#define VIDEO_PORT 12346          // Порт для приема видеопотока

// Функция для приема и отображения видеопотока
void receive_video_stream() {
    // Строка пайплайна GStreamer для OpenCV
    std::string gst_pipeline =
        "udpsrc port=" + std::to_string(VIDEO_PORT) + " ! "
        "application/x-rtp, encoding-name=H264 ! "
        "rtph264depay ! "
        "h264parse ! avdec_h264 ! videoconvert ! appsink";

    // Открываем видеопоток через OpenCV
    cv::VideoCapture cap(gst_pipeline, cv::CAP_GSTREAMER);
    if (!cap.isOpened()) {
        std::cerr << "Не удалось открыть видеопоток через GStreamer" << std::endl;
        return;
    }

    cv::Mat frame, rotatedFrame;
    while (true) {
        cap >> frame;  // Получаем кадр
        if (frame.empty()) {
            std::cerr << "Пустой кадр. Завершение..." << std::endl;
            break;
        }

        cv::rotate(frame, rotatedFrame, cv::ROTATE_180);

        cv::imshow("Video Stream", rotatedFrame);  // Отображаем кадр
        if (cv::waitKey(1) == 27) {  // Нажмите Esc для выхода
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization error." << std::endl;
        return -1;
    }

    // Создание сокета для отправки команд
    SOCKET command_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (command_sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket for commands." << std::endl;
        WSACleanup();
        return -1;
    }

    // Настройка адреса сервера для отправки команд
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Запуск потока для приема видеопотока
    std::thread videoThread(receive_video_stream);

    // Основной цикл обработки клавиш
    while (true) {
        if (_kbhit()) {  // Проверяем, была ли нажата клавиша
            char key = _getch();  // Считываем клавишу

            char command = 0;  // Команда, которая будет отправлена
            switch (key) {
                case 'w': command = '1'; break;
                case 's': command = '2'; break;
                case 'd': command = '3'; break;
                case 'a': command = '4'; break;
                case 72: command = '5'; break;  // Вверх
                case 80: command = '6'; break;  // Вниз
                case 75: command = '7'; break;  // Влево
                case 77: command = '8'; break;  // Вправо
            }

            if (command != 0) {
                // Отправляем команду на сервер
                sendto(command_sock, &command, sizeof(command), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
            }
        }
    }

    // Завершаем поток видеопотока
    videoThread.join();

    // Закрываем сокет и освобождаем ресурсы
    closesocket(command_sock);
    WSACleanup();
    return 0;
}
