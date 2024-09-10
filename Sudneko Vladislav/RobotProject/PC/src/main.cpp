#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "RobotController.hpp"

int main(int argc, char** argv) {
    RobotController robot("localhost", 5656, 5656);

    std::string rtsp_stream = "rtsp://localhost:8554/test";
    cv::VideoCapture cap(rtsp_stream);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open RTSP stream" << std::endl;
        return -1;
    }

    cv::Mat overlay_image = cv::imread("front.png", cv::IMREAD_UNCHANGED);
    if (overlay_image.empty()) {
        std::cerr << "Error: Unable to load overlay image" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Robot Control", cv::WINDOW_AUTOSIZE);
    
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Unable to capture video frame" << std::endl;
            break;
        }
    
        // Convert frame to 4 channels (RGBA) if it's not already
        if (frame.channels() == 3) {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2BGRA);
        }
    
        // Ensure overlay image fits within the frame
        if (overlay_image.cols > frame.cols || overlay_image.rows > frame.rows) {
            // Resize overlay image to fit within the frame
            cv::resize(overlay_image, overlay_image, cv::Size(frame.cols, frame.rows));
        }
    
        // Split the overlay into RGB and Alpha channels
        cv::Mat overlay_rgb, overlay_alpha;
        std::vector<cv::Mat> overlay_channels(4);
        cv::split(overlay_image, overlay_channels);
        overlay_rgb = cv::Mat(overlay_image.size(), CV_8UC3);
        cv::merge(std::vector<cv::Mat>{overlay_channels[0], overlay_channels[1], overlay_channels[2]}, overlay_rgb);
        overlay_alpha = overlay_channels[3];
    
        // Create a region of interest (ROI) in the frame where the overlay will be applied
        cv::Rect roi(cv::Point(0, 0), overlay_image.size());
        cv::Mat frame_roi = frame(roi);
    
        // Blend the overlay into the frame using the alpha channel
        for (int y = 0; y < overlay_image.rows; ++y) {
            for (int x = 0; x < overlay_image.cols; ++x) {
                cv::Vec4b& pixel = frame_roi.at<cv::Vec4b>(y, x); // Access frame pixel (with alpha)
                cv::Vec3b& overlay_pixel = overlay_rgb.at<cv::Vec3b>(y, x); // Access overlay pixel
                uchar alpha = overlay_alpha.at<uchar>(y, x); // Access overlay alpha channel
    
                // Perform alpha blending
                pixel[0] = (overlay_pixel[0] * alpha + pixel[0] * (255 - alpha)) / 255; // Blue
                pixel[1] = (overlay_pixel[1] * alpha + pixel[1] * (255 - alpha)) / 255; // Green
                pixel[2] = (overlay_pixel[2] * alpha + pixel[2] * (255 - alpha)) / 255; // Red
                pixel[3] = std::max(pixel[3], alpha); // Update alpha channel
            }
        }
    
        std::string displayText = "Distance to obstacle: 20 cm";
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        double fontScale = 0.5;
        int thickness = 1;
        int baseline = 0;
        cv::Size textSize = cv::getTextSize(displayText, fontFace, fontScale, thickness, &baseline);
    
        cv::Point textOrg(10, frame.rows - 10);
    
        cv::putText(frame, displayText, textOrg, fontFace, fontScale, cv::Scalar(255, 255, 255), thickness);
    
    
        cv::imshow("Robot Control", frame);
    
        char key = (char)cv::waitKey(30);
        if (key == 27) { 
            break;
        }
        else if (key == 'w') {
            robot.moveForward();
        }
        else if (key == 's') {
            robot.moveBackward();
        }
        else if (key == 'a') {
            robot.moveLeft();
        }
        else if (key == 'f') {
            robot.grabCatch();
        }
        else if (key == 'e') {
            robot.grabRelease();
        }
        else if (key == 'o') {
            robot.grabUp();
        }
        else if (key == 'l') {
            robot.grabDown();
        }
    }
    
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
