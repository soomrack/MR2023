#include <iostream>
#include <thread>
#include <chrono>

#include "orange_bot_keydetect.hpp"
#include "orange_bot_udp_server.hpp"
#include "orange_bot_udp_client.hpp"
#include "orange_bot_camera.hpp"

class keyboard keyboard;

class speed_control
{
public:
	int left = 0, right = 0;
	int status;
	int speed = 205;
	void push(int l, int r)
	{
		left = l;
		right = r;
	}
	void speed_change (const char* c)
	{
		c == "+" ? speed+=10 : speed-=10;
		if (speed > 255 ) speed = 255;
		if (speed < 5 ) speed = 5;
	}
}drive;

void key_detect()
{
	keyboard.init_keyboard();
	while(1)
	{
        keyboard.scan_keyboard();
		//printf("%d\n", keyboard.key_pressed);
		switch (keyboard.key_pressed)
		{
		case 117: //u
			drive.push(drive.speed - 100, drive.speed);
			break;
		case 105: //i
			drive.push(drive.speed, drive.speed);
			break;
		case 111: //o
			drive.push(drive.speed, drive.speed - 100);
			break;
		case 106: //j
			drive.push(-drive.speed, drive.speed);
			break;
		case 107: //k
			drive.push(0, 0);
			break;
		case 108: //l
			drive.push(drive.speed, -drive.speed);
			break;
		case 109: //m
			drive.push(-drive.speed + 100, -drive.speed);
			break;
		case 44: //,
			drive.push(-drive.speed, -drive.speed);
			break;	
		case 46: ///
			drive.push(-drive.speed, -drive.speed + 100);
			break;
		case 113: //q
			drive.speed_change("+");
			break;
		case 97: //a
			drive.speed = 205;
			break;	
		case 122: //z
			drive.speed_change("-");
			break;
		case 112: //p
			if (drive.status == 0)
				drive.status = 1;
			else drive.status = 0;
			break;
		case 121: //p
			if (drive.status == 0)
				drive.status = 2;
			else drive.status = 0;
			break;
		default:
			std::cout << keyboard.key_pressed << std::endl;
			break;
		}
	}
	keyboard.close_keyboard();
}

void transmit_speed()
{
	orange_bot_udp_server server_s(8081, 8082, "192.168.0.32"); //101
	
    server_s.create_server_socket();
    server_s.set_client_address();

	while(1)
	{
		server_s.transmit_speed_to_client(drive.left, drive.right, drive.status);
		std::cout << "PC:  " << drive.left << "," <<  drive.right << "," <<  drive.status << std::endl;
		usleep(20000);
		//std::cout << "Sent number to the client." << std::endl;
	}
}


void receive_video()
{
    orange_bot_udp_client client_v(8091);
    orange_bot_camera cam(320, 240); 

    client_v.create_client_socket();

    while (1){
        if (client_v.receive_frame_from_server() < 0)
			continue;
        cam.frame = client_v.frame;
        cam.show_frame("PC");

        if (cv::waitKey(1) == 27) {  // Нажмите ESC для выхода
            break;
        }
		usleep(20000);
    }
}


int main() {
	std::thread th1(key_detect);
	std::thread th2(transmit_speed);
	std::thread th3(receive_video);
	th1.join();
	th2.join();
	th3.join();
	
	return 0;
}