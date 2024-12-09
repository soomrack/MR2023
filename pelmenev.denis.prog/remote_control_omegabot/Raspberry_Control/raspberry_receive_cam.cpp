#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>
#include <pigpio.h>  // Для работы с GPIO (включая UART)
#include <gst/gst.h>

#define VIDEO_PORT 12346  // Порт для видеопотока
#define SERVER_PORT 12345 // Порт для приема команд
const char* UART_DEVICE = "/dev/ttyACM0";  // UART устройство
const char* SERVER_IP = "192.168.110.235";  // IP адрес ноутбука

void videoStreamSender() {
    // Инициализация GStreamer
    gst_init(nullptr, nullptr);

    // Создание элемента пайплайна GStreamer
    std::string pipelineStr =
    "libcamerasrc ! "
    "video/x-raw, width=640, height=480, framerate=30/1 ! "
    "videoflip method=vertical-flip ! videoflip method=horizontal-flip ! "
    "videoconvert ! "
    "x264enc tune=zerolatency bitrate=500 speed-preset=superfast ! "
    "rtph264pay ! "
    "udpsink host=" + std::string(SERVER_IP) + " port=" + std::to_string(VIDEO_PORT);
    
    GError* error = nullptr;
    GstElement* pipeline = gst_parse_launch(pipelineStr.c_str(), &error);

    if (!pipeline) {
        std::cerr << "Ошибка создания пайплайна GStreamer: " << (error ? error->message : "неизвестная ошибка") << std::endl;
        if (error) g_error_free(error);
        return;
    }

    // Запуск пайплайна
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "Не удалось запустить пайплайн GStreamer!" << std::endl;
        gst_object_unref(pipeline);
        return;
    }

    // Ожидание завершения (или можно сделать основной цикл)
    std::cout << "Видеопоток отправляется. Нажмите Ctrl+C для завершения." << std::endl;
    GstBus* bus = gst_element_get_bus(pipeline);
    gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    // Остановка пайплайна
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(bus);
    gst_object_unref(pipeline);
}

int main() {
    // Инициализация pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Ошибка инициализации pigpio" << std::endl;
        return -1;
    }

    // Открытие UART
    int uart = serOpen((char*)UART_DEVICE, 9600, 0);
    if (uart < 0) {
        std::cerr << "Ошибка открытия UART" << std::endl;
        gpioTerminate();
        return -1;
    }

    // Настройка сокета для приема данных по UDP
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        serClose(uart);
        gpioTerminate();
        return -1;
    }

    sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(SERVER_PORT);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (sockaddr*)&localAddr, sizeof(localAddr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        close(sock);
        serClose(uart);
        gpioTerminate();
        return -1;
    }

    // Запуск потока для видеопотока
    std::thread videoThread(videoStreamSender);

    // Основной цикл: прием команд и отправка в UART (закомментировано, так как UART не используется)
    while (true) {
        char buffer[1];
        sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);

        int received = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&clientAddr, &addrLen);
        if (received > 0) {
            serWriteByte(uart, buffer[0]);
            std::cout << "Получена команда: " << buffer[0] << std::endl;
        }
    }

    videoThread.join();  // Ожидаем завершения потока видеопотока

    close(sock);
    serClose(uart);
    gpioTerminate();
    return 0;
}
