#include "orange_bot_uart.hpp"

orange_bot_uart::orange_bot_uart(std::string port_name)
{
    serialPort = port_name; //"/dev/ttyUSB0"
}

orange_bot_uart::~orange_bot_uart()
{
    close(uart0_filestream);
}


void orange_bot_uart::open_port ()
{
    // Открываем порт UART
    uart0_filestream = open(serialPort.c_str(), O_RDWR | O_NOCTTY); //| O_NDELAY
    
    if (uart0_filestream == -1) {
        std::cerr << "Ошибка открытия UART.\n";
        uart_error = -1;
    }
}


int orange_bot_uart::configure_port()
{
    if (uart_error != 0) return -1;
    // Настройка параметров UART    
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B19200 | CS8 | CLOCAL | CREAD;  // Устанавливаем скорость 9600, 8 бит данных, включение приемника
    options.c_iflag = IGNPAR;                        // Игнорировать ошибки четности
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);             // Очистка входного буфера
    tcsetattr(uart0_filestream, TCSANOW, &options);  // Применение параметров
    return 0;
}

int orange_bot_uart::send_speed(int left, int right)
{
    tcflush(uart0_filestream, TCOFLUSH);  // Очистка буфера перед отправкой данных

    if (uart_error != 0) return -1;
    char buffer[20];

    // Форматируем данные в строку
    int len = snprintf(buffer, sizeof(buffer), "%d,%d\n", left, right);
    //std::cout << buffer;

    // Проверка доступности UART перед отправкой
    int flags = fcntl(uart0_filestream, F_GETFL, 0);
    if (flags & O_NONBLOCK) {
        std::cerr << "Буфер UART занят.\n";
        return -1;
    }

    // Передача данных по UART
    int count = write(uart0_filestream, buffer, len);
    if (count < 0) {
        std::cerr << "Ошибка передачи данных по UART.\n";
        return -1;
    }
    return 0;
}

int orange_bot_uart::receive_distance(int& front_distance)
{
    if (uart_error != 0) return -1;

    char buffer[256];
    int length = read(uart0_filestream, (void*)buffer, sizeof(buffer)); // Чтение данных из UART

    if (length < 0) {
        std::cerr << "Ошибка при чтении данных с UART.\n";
        return -1;
    }
    else if (length == 0) {
        std::cerr << "Нет данных для чтения.\n";
        return -1;
    }
    else {
        buffer[length] = '\0';
        front_distance = atoi(buffer);
    }
    return 0;
}


/*
int main() {
    orange_bot_uart uart("/dev/ttyUSB0");
    int left, right;

    uart.open_port();
    uart.configure_port();
    while (true)
    {
        std::cout << "left: ";
        std::cin >> left;
        std::cout << "right: ";
        std::cin >> right;
        uart.send_speed(left, right);
    }    
}*/