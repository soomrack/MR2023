import os

os.add_dll_directory(r"C:\\OpenCV\\opencv-4.9.0\\install\\bin\\")
os.add_dll_directory(r"C:\\GStreamer\\1.0\\msvc_x86_64\\bin")

import cv2
from ultralytics import YOLO
import threading

model = YOLO("yolov8n.pt")

gst_pipeline = (
    "udpsrc port=12346 caps=\"application/x-rtp, encoding-name=H264, payload=96\" ! "
    "rtph264depay ! avdec_h264 ! videoconvert ! appsink"
)

print("Opening videostream with OpenCV...")
cap = cv2.VideoCapture(gst_pipeline, cv2.CAP_GSTREAMER)

if not cap.isOpened():
    print("Error opening videostream.")
    exit()

print("Videostream is opened.")

frame_for_detection = None
frame_lock = threading.Lock()
detection_result = None

def detect_objects():
    global frame_for_detection, detection_result
    while True:
        local_frame = None
        with frame_lock:
            if frame_for_detection is not None:
                local_frame = frame_for_detection.copy()

        if local_frame is not None:
            resized_frame = cv2.resize(local_frame, (640, 640))
            results = model.predict(resized_frame, verbose=False)
            detection_result = results[0].plot()

threading.Thread(target=detect_objects, daemon=True).start()

while True:
    ret, frame = cap.read()
    if not ret:
        print("No frame.")
        break

    rotated = cv2.rotate(frame, cv2.ROTATE_180)

    cv2.imshow("Original", rotated)

    with frame_lock:
        frame_for_detection = rotated.copy()

    if detection_result is not None:
        cv2.imshow("YOLOv8n", detection_result)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
