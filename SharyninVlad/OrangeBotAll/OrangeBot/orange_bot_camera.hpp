#include <opencv2/opencv.hpp>

class orange_bot_camera
{
private:
    int IMG_WIDTH, IMG_HEIGHT;
public:
    cv::Mat frame;
    cv::VideoCapture cap;

public:
    orange_bot_camera(int width, int height );
    ~orange_bot_camera();
    int camera_connect();
    int get_frame();
    void show_frame(std::string frame_name);
    
};
