import socket
import keyboard


# Настройки Wi-Fi
raspberry_ip = '192.168.1.100'  # IP Raspberry Pi
raspberry_port = 12345           # Порт для связи с Raspberry Pi


# Создание сокета
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


# Функция отправки команды
def send_command(command):
    sock.sendto(command.encode(), (raspberry_ip, raspberry_port))


# Основной цикл для обработки клавиш
try:
    while True:
        if keyboard.is_pressed('w'):
            send_command('1')
        elif keyboard.is_pressed('s'):
            send_command('2')
        elif keyboard.is_pressed('d'):
            send_command('3')
        elif keyboard.is_pressed('a'):
            send_command('4')
        elif keyboard.is_pressed('up'):
            send_command('5')
        elif keyboard.is_pressed('down'):
            send_command('6')
        elif keyboard.is_pressed('left'):
            send_command('7')
        elif keyboard.is_pressed('right'):
            send_command('8')

finally:
    sock.close()
