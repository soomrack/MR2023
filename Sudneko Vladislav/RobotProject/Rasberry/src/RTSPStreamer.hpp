#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <string>
#include <iostream>
#include <thread>
#include <atomic>

class RTSPStreamer {
public:
    RTSPStreamer() : server(nullptr), media_factory(nullptr), loop(nullptr), running(false) {
        gst_init(nullptr, nullptr);
    }

    ~RTSPStreamer() {
        stop_stream();
        if (server) {
            g_object_unref(server);
        }
        if (media_factory) {
            g_object_unref(media_factory);
        }
        if (loop) {
            g_main_loop_unref(loop);
        }
    }

    bool start_stream(const std::string& mount_point, const std::string& pipeline_description) {
        if (running.load()) {
            std::cerr << "Stream is already running!" << std::endl;
            return false;
        }

        server = gst_rtsp_server_new();
        GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);

        media_factory = gst_rtsp_media_factory_new();
        gst_rtsp_media_factory_set_launch(media_factory, pipeline_description.c_str());

        gst_rtsp_mount_points_add_factory(mounts, mount_point.c_str(), media_factory);
        g_object_unref(mounts);

        if (gst_rtsp_server_attach(server, nullptr) == 0) {
            std::cerr << "Failed to attach the server" << std::endl;
            return false;
        }

        running.store(true);
        loop_thread = std::thread([this]() { run_main_loop(); });

        std::cout << "Stream is available at rtsp://127.0.0.1:8554" << mount_point << std::endl;
        return true;
    }

    void stop_stream() {
        if (running.load()) {
            if (loop) {
                g_main_loop_quit(loop);
                if (loop_thread.joinable()) {
                    loop_thread.join();
                }
            }
            running.store(false);
        }
    }

private:
    GstRTSPServer *server;
    GstRTSPMediaFactory *media_factory;
    GMainLoop *loop;
    std::thread loop_thread;
    std::atomic<bool> running;

    void run_main_loop() {
        loop = g_main_loop_new(nullptr, FALSE);
        g_main_loop_run(loop);
    }
};
