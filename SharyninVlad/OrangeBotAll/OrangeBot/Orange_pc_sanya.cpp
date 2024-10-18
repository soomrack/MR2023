#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <opencv2/opencv.hpp>

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
} drive;

// Глобальные переменные для управления качеством видео и записью
int video_quality = 2;  // Стандартное качество
cv::VideoWriter video_writer;
bool is_recording = false;

// Функция изменения качества видео
void adjust_video_quality(orange_bot_camera &cam, int quality)
{
    switch (quality) {
    case 1:
        cam.set_resolution(160, 120);  // Низкое качество
        break;
    case 2:
        cam.set_resolution(320, 240);  // Среднее качество
        break;
    case 3:
        cam.set_resolution(640, 480);  // Высокое качество
        break;
    default:
        cam.set_resolution(320, 240);  // Стандартное качество
        break;
    }
    std::cout << "Video quality set to level: " << quality << std::endl;
}

// Функция записи видео с телеметрией
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

// Функция добавления телеметрии в видео
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

// Функция для обнаружения нажатия клавиш
void key_detect(orange_bot_camera &cam)
{
	keyboard.init_keyboard();
	while(1)
	{
        keyboard.scan_keyboard();
		switch (keyboard.key_pressed)
		{
		case 117: // u
			drive.push(drive.speed - 100, drive.speed);
			break;
		case 105: // i
			drive.push(drive.speed, drive.speed);
			break;
		case 111: // o
			drive.push(drive.speed, drive.speed - 100);
			break;
		case 106: // j
			drive.push(-drive.speed, drive.speed);
			break;
		case 107: // k
			drive.push(0, 0);
			break;
		case 108: // l
			drive.push(drive.speed, -drive.speed);
			break;
		case 109: // m
			drive.push(-drive.speed + 100, -drive.speed);
			break;
		case 44: // ,
			drive.push(-drive.speed, -drive.speed);
			break;	
		case 46: // .
			drive.push(-drive.speed, -drive.speed + 100);
			break;
		case 113: // q
			drive.speed_change("+");
			break;
		case 97: // a
			drive.speed = 205;
			break;	
		case 122: // z
			drive.speed_change("-");
			break;
		case 49: // '1' - Низкое качество видео
			video_quality = 1;
			adjust_video_quality(cam, video_quality);
			break;
		case 50: // '2' - Среднее качество видео
			video_quality = 2;
			adjust_video_quality(cam, video_quality);
			break;
		case 51: // '3' - Высокое качество видео
			video_quality = 3;
			adjust_video_quality(cam, video_quality);
			break;
		case 114: // 'r' - Начало или остановка записи видео
			toggle_video_recording(cam);
			break;
		default:
			std::cout << keyboard.key_pressed << std::endl;
			break;
		}
	}
	keyboard.close_keyboard();
}

// Функция передачи скорости и телеметрии
void transmit_speed()
{
	orange_bot_udp_server server_s(8081, 8082, "192.168.0.32");

	server_s.create_server_socket();
	server_s.set_client_address();

	while(1)
	{
		auto now = std::chrono::system_clock::now();
		std::time_t current_time = std::chrono::system_clock::to_time_t(now);

		server_s.transmit_speed_to_client(drive.left, drive.right, drive.status);
		std::cout << "PC:  " << drive.left << "," <<  drive.right << "," <<  drive.status 
				  << " Time: " << std::ctime(&current_time);  // Время в телеметрии
		usleep(20000);
	}
}

// Функция получения и отображения видео
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

        record_video_with_telemetry(cam);  // Запись видео с телеметрией

        if (cv::waitKey(1) == 27) {  // Нажмите ESC для выхода
            break;
        }
		usleep(20000);
    }
}

int main() {
	std::thread th1(key_detect, std::ref(cam));
	std::thread th2(transmit_speed);
	std::thread th3(receive_video);

	th1.join();
	th2.join();
	th3.join();
	
	return 0;
}
