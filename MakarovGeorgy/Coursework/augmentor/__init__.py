from .core import *
from .augmentations import *


class Augmentor:
    ALLOWED_FORMATS = ("COCO", "CVAT", "YOLO")

    def __new__(cls, fmt: str, debug: bool = False, log_path: str = None):
        if fmt not in cls.ALLOWED_FORMATS:
            raise ValueError("Unsupported dataset format")

        if fmt == cls.ALLOWED_FORMATS[0]:
            raise ValueError("COCO dataset format is not implemented yet")

        if fmt == cls.ALLOWED_FORMATS[1]:
            raise ValueError("CVAT dataset format is not implemented yet")

        if fmt == cls.ALLOWED_FORMATS[2]:
            return YOLO(debug, log_path)
