#ifndef VIDEOCAPTUREHANDLER
#define VIDEOCAPTUREHANDLER

#include <iostream>
#include <cstdlib>
#include <string>
#include <csignal>

class VideoCaptureHandler {
public:
    int gstStreamPID = -1;  // ID процесса стрима
    std::string ipAddress;
    int udpPort = 8888;
    int videoCounter = 1;

    VideoCaptureHandler(const std::string& ip) : ipAddress(ip) {}

    void startStreamingAndRecording() {
        std::string command = "gst-launch-1.0 rpicamsrc ! video/x-h264, width=640, height=480, framerate=30/1 ! h264parse ! tee name=t "
                              "t. ! queue ! matroskamux ! filesink location=video_capture_" + std::to_string(videoCounter) + ".mkv "
                              "t. ! queue ! rtph264pay config-interval=1 pt=96 ! udpsink host=" + ipAddress + " port=" + std::to_string(udpPort) + " & echo $!";
        gstStreamPID = std::system(command.c_str());
        std::cout << "Started streaming to " << ipAddress << ":" << udpPort << " and recording to video_capture_" << videoCounter << ".mkv (PID: " << gstStreamPID << ")" << std::endl;
    }

    void stopStreamingAndRecording() {
        if (gstStreamPID != -1) {
            std::string command = "kill " + std::to_string(gstStreamPID);
            std::system(command.c_str());
            std::cout << "Stopped streaming and recording (PID: " << gstStreamPID << ")" << std::endl;
            gstStreamPID = -1;
            videoCounter++;
        } else {
            std::cout << "No active stream to stop." << std::endl;
        }
    }
};

#endif // VIDEOCAPTUREHANDLER
