import socket
import serial


# Настройки UART
ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)


# Настройки Wi-Fi
local_ip = '192.168.1.100'  # IP Raspberry Pi
local_port = 12345          # Порт для получения команд


# Создание сокета
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((local_ip, local_port))


# Основной цикл для приёма данных
try:
    while True:
        data, addr = sock.recvfrom(1024)
        command = data.decode()
        ser.write(command.encode())  # Отправка данных на Arduino через UART


finally:
    sock.close()
    ser.close()
