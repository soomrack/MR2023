#ifndef VIDEOCAPTUREHANDLER
#define VIDEOCAPTUREHANDLER

#include <iostream>
#include <cstdlib>
#include <string>

class VideoCaptureHandler {
public:
    int videoCounter = 1;
    int gstProcessID = -1;

    void startVideoCapture() {
        std::string command = "gst-launch-1.0 -e v4l2src ! videoconvert ! x264enc ! mp4mux ! filesink location=video_capture_"
                              + std::to_string(videoCounter) + ".mp4 & echo $!";
        gstProcessID = std::system(command.c_str());
        std::cout << "Started capturing video_capture_" << videoCounter << ".mp4 (PID: " << gstProcessID << ")" << std::endl;
    }

    void stopVideoCapture() {
        if (gstProcessID != -1) {
            std::string command = "kill " + std::to_string(gstProcessID);
            std::system(command.c_str());
            std::cout << "Stopped capturing video with PID: " << gstProcessID << std::endl;
            videoCounter++;
            gstProcessID = -1;
        } else {
            std::cout << "No active video capture to stop." << std::endl;
        }
    }
};

#endif // VIDEOCAPTUREHANDLER