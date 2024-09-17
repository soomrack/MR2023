#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    GstRTSPServer *server = gst_rtsp_server_new();
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();

    gst_rtsp_media_factory_set_launch(factory, "( autovidesrc ! video/x-h264,width=1280,height=720,framerate=30/1 ! x264enc tune=zerolatency ! rtph264pay name=pay0 pt=96 )");
    gst_rtsp_mount_points_add_factory(mounts, "/omegabot_stream", factory);

    g_object_unref(mounts);
    gst_rtsp_server_attach(server, NULL);

    g_print("Stream ready at rtsp://127.0.0.1:8554/omegabot_stream\n");

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_main_loop_unref(loop);
    g_object_unref(server);

    return 0;
}
