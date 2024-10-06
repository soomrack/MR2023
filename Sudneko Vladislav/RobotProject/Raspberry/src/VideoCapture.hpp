#ifndef VIDEOCAPTUREHANDLER
#define VIDEOCAPTUREHANDLER

#include <iostream>
#include <cstdlib>
#include <string>
#include <csignal>

class VideoCaptureHandler {
public:
    int videoCounter = 1;
    int gstStreamPID = -1;  // ID процесса стрима
    int gstCapturePID = -1; // ID процесса видеозахвата
    std::string ipAddress;
    int udpPort = 8888;

    VideoCaptureHandler(const std::string& ip) : ipAddress(ip) {}

    void startStreaming() {
        std::string command = "gst-launch-1.0 rpicamsrc ! video/x-h264, width=640, height=480, framerate=30/1 ! rtph264pay config-interval=1 pt=96 ! "
                              "udpsink host=" + ipAddress + " port=" + std::to_string(udpPort) + " & echo $!";
        gstStreamPID = std::system(command.c_str());
        std::cout << "Started streaming to " << ipAddress << ":" << udpPort << " (PID: " << gstStreamPID << ")" << std::endl;
    }

    void stopStreaming() {
        if (gstStreamPID != -1) {
            std::string command = "kill " + std::to_string(gstStreamPID);
            std::system(command.c_str());
            std::cout << "Stopped streaming (PID: " << gstStreamPID << ")" << std::endl;
            gstStreamPID = -1;
        } else {
            std::cout << "No active stream to stop." << std::endl;
        }
    }

    void startVideoCapture() {
        if (gstStreamPID != -1) {
            stopStreaming(); 
        }
        std::string command = "gst-launch-1.0 -e v4l2src ! videoconvert ! x264enc ! mp4mux ! filesink location=video_capture_"
                              + std::to_string(videoCounter) + ".mp4 & echo $!";
        gstCapturePID = std::system(command.c_str());
        std::cout << "Started capturing video_capture_" << videoCounter << ".mp4 (PID: " << gstCapturePID << ")" << std::endl;
    }

    void stopVideoCapture() {
        if (gstCapturePID != -1) {
            std::string command = "kill " + std::to_string(gstCapturePID);
            std::system(command.c_str());
            std::cout << "Stopped capturing video with PID: " << gstCapturePID << std::endl;
            videoCounter++;
            gstCapturePID = -1;
            startStreaming(); 
        } else {
            std::cout << "No active video capture to stop." << std::endl;
        }
    }
};

#endif // VIDEOCAPTUREHANDLER
