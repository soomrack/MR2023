#include <gst/gst.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "RobotController.hpp"
#include <thread>
#include <chrono>
#include <functional>

static GstElement *pipeline;

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            std::cout << "End of stream" << std::endl;
            g_main_loop_quit((GMainLoop *)data);
            break;
        case GST_MESSAGE_ERROR:
            {
                gchar *debug;
                GError *error;
                gst_message_parse_error(msg, &error, &debug);
                std::cerr << "Error: " << error->message << std::endl;
                g_free(debug);
                g_error_free(error);
                g_main_loop_quit((GMainLoop *)data);
                break;
            }
        default:
            break;
    }
    return TRUE;
}

void send_heartbeat(RobotController &robot) {
    while (true) {
        robot.sendHeartbeat();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    pipeline = gst_parse_launch(
        "udpsrc port=8888 caps=\"application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96\" ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink",
        NULL);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Robot Control App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    GstBus *bus = gst_element_get_bus(pipeline);
    gst_bus_add_watch(bus, bus_call, loop);
    gst_object_unref(bus);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    RobotController robot = RobotController("http://192.168.24.84:5000");

    // std::thread heartbeat_sender = std::thread(send_heartbeat, std::ref(robot));

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        std::cout << "Move forward" << std::endl;
                        robot.moveForward();
                        break;
                    case SDLK_a:
                        std::cout << "Turn left" << std::endl;
                        robot.moveLeft();
                        break;
                    case SDLK_s:
                        std::cout << "Move backward" << std::endl;
                        robot.moveBackward();
                        break;
                    case SDLK_d:
                        std::cout << "Turn right" << std::endl;
                        robot.moveRight();
                        break;
                    default:
                        break;
                }
            }
        }

        // Process GStreamer events
        g_main_context_iteration(NULL, FALSE);
    }

    // Clean up
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    SDL_DestroyWindow(window);
    SDL_Quit();
    g_main_loop_unref(loop);

    return 0;
}