#include <iostream>
#include <fcntl.h>      // Для функций open()
#include <unistd.h>     // Для функций write(), close()
#include <termios.h>    // Для управления UART

class orange_bot_uart
{
public:
    std::string serialPort;
    int uart0_filestream;
    struct termios options;
    int uart_error = 0;

public:
    orange_bot_uart(std::string port_name);
    ~orange_bot_uart();    
    void open_port();
    int configure_port();
    int send_speed(int left, int right);
};