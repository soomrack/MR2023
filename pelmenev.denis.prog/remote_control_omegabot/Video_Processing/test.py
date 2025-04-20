import os
import sys

# Укажи путь до папки bin и lib GStreamer из conda, адаптируй под свою систему
conda_env_path = os.environ.get("CONDA_PREFIX", "C:\\Users\\1\\miniconda3\\envs\\yolovideo\\")

# Добавляем пути к нужным библиотекам
os.environ["PATH"] += os.pathsep + os.path.join(conda_env_path, "Library", "bin")
os.environ["GI_TYPELIB_PATH"] = os.path.join(conda_env_path, "Library", "lib", "girepository-1.0")
os.environ["GST_PLUGIN_PATH"] = os.path.join(conda_env_path, "Library", "lib", "gstreamer-1.0")

# Только потом импортируем gi
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst

Gst.init(None)
pipeline = Gst.parse_launch("videotestsrc ! autovideosink")
pipeline.set_state(Gst.State.PLAYING)

import time
time.sleep(5)
pipeline.set_state(Gst.State.NULL)
