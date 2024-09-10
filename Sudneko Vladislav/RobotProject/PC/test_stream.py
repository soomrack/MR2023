import gi
gi.require_version('Gst', '1.0')
gi.require_version('GstRtspServer', '1.0')
from gi.repository import Gst, GstRtspServer, GObject, GLib

# Инициализация GStreamer
Gst.init(None)

class MyFactory(GstRtspServer.RTSPMediaFactory):
    def __init__(self):
        super(MyFactory, self).__init__()

    def do_create_element(self, url):
        print("Создаем pipeline для стрима RTSP")
        # Создаем pipeline для захвата видео с камеры и кодирования
        pipeline_str = (
            "avfvideosrc ! video/x-raw, width=640, height=480, framerate=30/1 ! "
            "videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=superfast ! "
            "rtph264pay config-interval=1 name=pay0 pt=96"
        )
        return Gst.parse_launch(pipeline_str)

class GstServer:
    def __init__(self):
        # Создаем RTSP сервер
        self.server = GstRtspServer.RTSPServer()
        self.server.props.service = "8554"  # Порт RTSP сервера (можно поменять)
        
        factory = MyFactory()
        factory.set_shared(True)

        # Добавляем новый mount point для стрима
        mount_points = self.server.get_mount_points()
        mount_points.add_factory("/test", factory)

        self.server.attach(None)
        print("RTSP сервер запущен на rtsp://localhost:8554/test")

if __name__ == "__main__":
    server = GstServer()
    # Запускаем основной цикл GLib, чтобы сервер работал
    loop = GLib.MainLoop()
    loop.run()
