#include <thread>
#include <chrono>

#include "PCCommunicator.hpp"
// #include "ArduinoCommunicator.hpp"
// #include "RTSPStreamer.hpp"

// Consts
const bool run = true;

int main() {
    PCCommunicator pc_communicator();
    // ArduinoCommunicator arduino_comminicator(arduino_address);
    // RTSPStreamer rtsp_streamer;

    // Start RTSP stream
    // std::string pipeline_description = "( v4l2src device=/dev/video0 ! video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! rtph264pay name=pay0 pt=96 )";
    // streamer.start_stream("/omegabot_stream", pipeline_description);

    while (run) {
        // Listen sensors data from Arduino and send to the GCS

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Listen command data from GCS and send to arduino
        // arduino_comminicator.move(gcs_communicator.get_command());
    }

    return 0;
}