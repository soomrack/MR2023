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
        if (!server) {
            std::cerr << "Failed to create RTSP server" << std::endl;
            return false;
        }

        GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
        if (!mounts) {
            std::cerr << "Failed to get mount points" << std::endl;
            g_object_unref(server);
            server = nullptr;
            return false;
        }

        media_factory = gst_rtsp_media_factory_new();
        if (!media_factory) {
            std::cerr << "Failed to create media factory" << std::endl;
            g_object_unref(mounts);
            g_object_unref(server);
            server = nullptr;
            return false;
        }

        gst_rtsp_media_factory_set_launch(media_factory, pipeline_description.c_str());
        gst_rtsp_mount_points_add_factory(mounts, mount_point.c_str(), media_factory);
        g_object_unref(mounts);

        if (gst_rtsp_server_attach(server, nullptr) == 0) {
            std::cerr << "Failed to attach the server" << std::endl;
            g_object_unref(media_factory);
            media_factory = nullptr;
            g_object_unref(server);
            server = nullptr;
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
                g_main_loop_unref(loop);
                loop = nullptr;
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
        if (loop) {
            g_main_loop_run(loop);
        }
    }
};
