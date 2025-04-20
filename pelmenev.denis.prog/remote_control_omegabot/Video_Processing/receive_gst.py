import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GObject

Gst.init(None)

def on_message(bus, message, loop):
    t = message.type
    if t == Gst.MessageType.EOS:
        print("End of stream")
        loop.quit()
    elif t == Gst.MessageType.ERROR:
        err, debug = message.parse_error()
        print(f"Error: {err}, {debug}")
        loop.quit()

# Пример: приём H264-потока через UDP (порт 12346)
pipeline_str = (
    "udpsrc port=12346 caps=\"application/x-rtp, media=video, "
    "encoding-name=H264, payload=96\" ! "
    "rtph264depay ! avdec_h264 ! videoconvert ! autovideosink"
)

pipeline = Gst.parse_launch(pipeline_str)
loop = GObject.MainLoop()

bus = pipeline.get_bus()
bus.add_signal_watch()
bus.connect("message", on_message, loop)

pipeline.set_state(Gst.State.PLAYING)
print("Receiving video stream... Ctrl+C to stop.")
try:
    loop.run()
except KeyboardInterrupt:
    pass
finally:
    pipeline.set_state(Gst.State.NULL)
