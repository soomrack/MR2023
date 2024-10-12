#include "orange_bot_udp_client.hpp"
#include "orange_bot_udp_server.hpp"
#include "orange_bot_camera.hpp"
#include "orange_bot_uart.hpp"
#include "orange_bot_keydetect.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <mutex>

struct speed
{
    int left = 0, right = 0;
    int time_error = 0;
}speed;


void receive_speed()
{
    orange_bot_udp_client client_s(8081);

    client_s.create_client_socket();

    while (1)
    {
        client_s.receive_speed_from_server(&speed.left, &speed.right);
        speed.time_error = 0;
        //std::cout << "BOT:" << speed.left << "," << speed.right << std::endl;
        usleep(10000);
    }    
}


void transmit_video()
{
	orange_bot_udp_server server_v(8091, 8092, "192.168.0.12");
	
    server_v.create_server_socket();
    server_v.set_client_address();
    
	orange_bot_camera cam(640, 480);    
    cam.camera_connect();

    while (true) {
        cam.get_frame();
		cv::flip(cam.frame, cam.frame, 0);
		cv::flip(cam.frame, cam.frame, 1);
        /*cam.show_frame("bot");
        if (cv::waitKey(1) == 27) {  // Нажмите ESC для выхода
            break;
        }*/
		server_v.transmit_frame_to_client(cam.frame);
        usleep(10000);
    }  
}

void transmit_speed_to_arduino()
{
    orange_bot_uart uart("/dev/ttyUSB0");
    int left, right;

    uart.open_port();
    uart.configure_port();
    while (true)
    {
        //std::cout << "Arduino:  " << speed.left << "," << speed.right << std::endl;
        uart.send_speed(speed.left,speed.right);
        uart.receive_distance();
        std::cout << uart.front_distance << std::endl;
        usleep(10000);
    }     
}

void timer_error()
{
    while (1)
    {
        speed.time_error++;
        if (speed.time_error > 8)
        {
            speed.left = 0;
            speed.right = 0;
            speed.time_error = 8;
        }
        //std::cout << "time_error:" << speed.time_error << std::endl;
        usleep(10000);
    }
}


int main() 
{
    std::thread th1(receive_speed);
	std::thread th2(transmit_video);
    std::thread th3(transmit_speed_to_arduino);
    std::thread th4(timer_error);
	th1.join();
	th2.join();
    th3.join();
    th4.join();
}