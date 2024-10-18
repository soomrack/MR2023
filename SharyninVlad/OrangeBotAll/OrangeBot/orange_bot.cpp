
#include "orange_bot_udp_client.hpp"
#include "orange_bot_udp_server.hpp"
#include "orange_bot_camera.hpp"
#include "orange_bot_uart.hpp"
#include "orange_bot_keydetect.hpp"

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <time.h>
#include <mutex>

struct speed
{
    int left = 0, right = 0;
    int status = 0;
    int time_error = 0;
}speed;


void receive_speed()
{
    orange_bot_udp_client client_s(8081);

    client_s.create_client_socket();

    while (1)
    {
        client_s.receive_speed_from_server(&speed.left, &speed.right, &speed.status);
        speed.time_error = 0;
        std::cout << "BOT:" << speed.left << "," << speed.right << "," << speed.status << std::endl;
        usleep(10000);
    }    
}


void transmit_video()
{
	orange_bot_udp_server server_v(8091, 8092, "192.168.0.100"); //0.12
	
    server_v.create_server_socket();
    server_v.set_client_address();
    
	orange_bot_camera cam(320, 240);    
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

void add_to_file(int number)
{
    std::ofstream out("back_box.txt", std::ios::app);
    if (out.is_open())
        out << std::to_string(number) << std::endl;
    out.close();
}

void transmit_speed_to_arduino()
{
    orange_bot_uart uart("/dev/ttyUSB0");
    double start_time, end_time, period;
    int time_flag = 0;
    uart.open_port();
    uart.configure_port();
    while (true)
    {
        if (uart.front_distance < 10)
            if (speed.left > 0 || speed.right > 0)
            {
                speed.left = 0;
                speed.right = 0;
            }
        if (speed.status == 2 && time_flag == 0)
	{
            start_time = clock();
            time_flag = 1;
        }
	
        if (speed.status == 0 && time_flag == 1)
          time_flag = 0;

        if (speed.status == 2)
        {
            end_time = clock();
            period = (end_time - start_time) / CLOCKS_PER_SEC / 2 * 10;
            //std::cout << "period" << period << std::endl;
        }

	if (speed.status == 2)
        {
            if (period > 0 && period < 4)
		{
			speed.left = 205;
                	speed.right = 205;
		}
		if (period > 4 && period < 6.2)
                { 
                        speed.left = -205;
                        speed.right = 205;
                }
		if (period > 6.2 && period < 10)
                { 
                        speed.left = 205;
                        speed.right = 205;
                }
        }

        //std::cout << "Arduino:  " << speed.left << "," << speed.right << std::endl;
        uart.send_speed(speed.left,speed.right,speed.status);
        uart.receive_distance();
        //std::cout << "Front_distatce:  " << uart.front_distance << std::endl;
	if (speed.status == 1){
	    std::cout << "black_box: "<< uart.black_box << std::endl;
            add_to_file(uart.black_box);
            //uart.black_box = 0;
        }
       //std::cout << uart.front_distance << std::endl;
        usleep(10000);
    }     
}

void timer_error()
{
    while (1)
    {
        speed.time_error++;
        if (speed.time_error > 20 && speed.time_error <= 100)
        {
            speed.left = 0;
            speed.right = 0;
        }

        if (speed.time_error > 100 && speed.time_error <= 500)
        {
            speed.left = -210;
            speed.right = -210;
        }

        if (speed.time_error > 500)
        {
            speed.left = 0;
            speed.right = 0;
            speed.time_error = 501;
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
