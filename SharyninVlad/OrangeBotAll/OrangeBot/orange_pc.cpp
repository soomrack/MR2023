#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <fstream>

#include "orange_bot_keydetect.hpp"
#include "orange_bot_udp_server.hpp"
#include "orange_bot_udp_client.hpp"
#include "orange_bot_camera.hpp"

int IMG_HEIGHT = 240;
int IMG_WIDTH = 320;
int quality = 2;
cv::VideoWriter video_writer;
bool is_recording = false;

orange_bot_camera cam(IMG_WIDTH, IMG_HEIGHT);

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
	void speed_change(const char* c)
	{
		c == "+" ? speed += 10 : speed -= 10;
		if (speed > 255) speed = 255;
		if (speed < 5) speed = 5;
	}
}drive;

// Запись видео с телеметрией
void toggle_video_recording(orange_bot_camera &cam)
{
	if (!is_recording) {
		video_writer.open("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(320, 240), true);
		if (video_writer.isOpened()) {
			is_recording = true;
			std::cout << "Recording started." << std::endl;
		}
	} else {
		is_recording = false;
		video_writer.release();
		std::cout << "Recording stopped." << std::endl;
	}
}


// Добавления телеметрии в видео
void record_video_with_telemetry(orange_bot_camera &cam)
{
	auto now = std::chrono::system_clock::now();
	std::time_t current_time = std::chrono::system_clock::to_time_t(now);

	cv::Mat frame_with_telemetry = cam.frame.clone();
	cv::putText(frame_with_telemetry, std::string("Time: ") + std::ctime(&current_time), 
                cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

	cv::putText(frame_with_telemetry, std::string("Left: ") + std::to_string(drive.left) + 
                " Right: " + std::to_string(drive.right), 
                cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

	if (is_recording && video_writer.isOpened()) {
		video_writer.write(frame_with_telemetry);
	}
}


// Сохранение телеметрии в файл
void save_telemetry_to_file()
{
	std::ofstream telemetry_file;
	telemetry_file.open("telemetry.txt", std::ios_base::app);  // Открываем файл для добавления

	auto now = std::chrono::system_clock::now();
	std::time_t current_time = std::chrono::system_clock::to_time_t(now);

	if (telemetry_file.is_open()) {
		telemetry_file << "Time: " << std::ctime(&current_time);
		telemetry_file << "Left: " << drive.left << ", Right: " << drive.right << ", Status: " << drive.status << "\n";
		telemetry_file.close();
		std::cout << "Telemetry saved to file." << std::endl;
	} else {
		std::cout << "Failed to open telemetry file." << std::endl;
	}
}


void key_detect()
{
	keyboard.init_keyboard();
	while (1)
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
		case 114: //r - Начало или остановка записи видео
			toggle_video_recording(cam);
			break;
		case 116: //t - Сохранение телеметрии в файл
			save_telemetry_to_file();
			break;
		case 328:
			if (quality < 3) 
			{
				quality += 1;
				if (quality == 2) {
					IMG_HEIGHT = 240;
					IMG_WIDTH = 320;
				}
				else {
					IMG_HEIGHT = 480;
					IMG_WIDTH = 640;
				}
			}
		case 336:
			if (quality < 1)
			{
				quality -= 1;
				if (quality == 2) {
					IMG_HEIGHT = 240;
					IMG_WIDTH = 320;
				}
				else {
					IMG_HEIGHT = 120;
					IMG_WIDTH = 160;
				}
			}
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

	while (1)
	{
		auto now = std::chrono::system_clock::now();
		std::time_t current_time = std::chrono::system_clock::to_time_t(now);

		server_s.transmit_speed_to_client(drive.left, drive.right, drive.status, IMG_WIDTH, IMG_HEIGHT);
		std::cout << "PC:  " << drive.left << "," << drive.right << "," << drive.status
				  << " Time: " << std::ctime(&current_time);
		usleep(20000);
		//std::cout << "Sent number to the client." << std::endl;
	}
}


void receive_video()
{
	orange_bot_udp_client client_v(8091);


	client_v.create_client_socket();

	while (1) {
		if (client_v.receive_frame_from_server() < 0)
			continue;
		cam.frame = client_v.frame;
		cam.show_frame("PC");

		record_video_with_telemetry(cam);

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