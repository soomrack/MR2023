#include "GCSCommunicator.hpp"
#include "ArduinoCommunicator.hpp"
#include "RTSPStreamer.hpp"

// Consts
const int arduino_address = 0x08;
const std::string gcs_host = "localhost";
const int gcs_recv_port = 5656;
const int gcs_send_port = 5656;
const bool run = true;

int main() {
    GCSCommunicator gcs_communicator(gcs_host, gcs_recv_port, gcs_send_port);
    ArduinoCommunicator arduino_comminicator(arduino_address);
    RTSPStreamer rtsp_streamer;

    // Start RTSP stream
    std::string pipeline_description = "( v4l2src device=/dev/video0 ! video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! rtph264pay name=pay0 pt=96 )";
    streamer.start_stream("/omegabot_stream", pipeline_description);

    while (run) {
        // Listen sensors data from Arduino and send to the GCS
        gcs_communicator.send_distance(
            arduino_comminicator.get_distance_direction(),
            arduino_comminicator.get_distance());

        // Listen command data from GCS and send to arduino
        arduino_comminicator.move(gcs_communicator.get_command());
    }

    return 0;
}