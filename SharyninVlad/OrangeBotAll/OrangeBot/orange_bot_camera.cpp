#include "orange_bot_camera.hpp"


orange_bot_camera::orange_bot_camera(int width, int height)
{
    IMG_WIDTH = width; 
    IMG_HEIGHT = height;
}


orange_bot_camera::~orange_bot_camera()
{    
    cap.release();  // Освобождаем ресурс
    cv::destroyAllWindows();    //удаляем окно
}


int orange_bot_camera::camera_connect()
{
    cap.open(0);
    //проверка открытия камеры
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        return -1;
    }
    // Устанавливаем частоту кадров в 30 FPS
    cap.set(cv::CAP_PROP_FPS, 30);
    //устанавливаем высоту и ширину кадра
    cap.set(cv::CAP_PROP_FRAME_WIDTH, IMG_WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, IMG_HEIGHT);

    return 0;
}


int orange_bot_camera::get_frame()
{
    cap >> frame;  // Захват кадра
    if (frame.empty()) {
        std::cerr << "Error: Empty frame" << std::endl;
        return -1;
    }
    return 0;
}


void orange_bot_camera::show_frame(std::string frame_name)
{
    cv::resize(frame, frame, cv::Size(640, 480));
    cv::imshow(frame_name, frame);  // Отображение кадра
}


/*
int main() {
    orange_bot_camera cam;
    
    cam.cam_connect();

    while (true) {
        cam.get_frame();
        cam.show_frame();
        if (cv::waitKey(1) == 27) {  // Нажмите ESC для выхода
            break;
        }
    }    
    return 0;
}*/
