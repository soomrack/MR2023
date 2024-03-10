import numpy as np
from PIL import Image, ImageDraw


def subset_upper(subset: str) -> str:
    """
    Take a subset shortened name and return a subset name that starts with uppercase letter. Used for log formatting
    :param subset: *train*, *val* or *test*
    :return: *Training*, *Validation* or *Testing*
    """
    return "Training" if subset == "train" else "Validation" if subset == "val" else "Testing"


def subset_lower(subset: str) -> str:
    """
    Take a subset shortened name and return a subset name with all letters in lowercase. Used for log formatting
    :param subset: *train*, *val* or *test*
    :return: *training*, *validation* or *testing*
    """
    return "training" if subset == "train" else "validation" if subset == "val" else "testing"


def draw_bboxes(image: np.ndarray, bboxes: list) -> np.ndarray:
    """
    Draw bounding boxes on the image for debugging purposes. The image is processed as NumPy array, so additional
    transition to PIL might be needed to see the results. The bounding boxes outline is of red color with pixel width 2
    :param image: image as NumPy array
    :param bboxes: bounding boxes list of (x, y, w, h, class)
    :return: image with drawn bounding boxes on it
    """
    drawn_image = Image.fromarray(image)
    draw = ImageDraw.Draw(drawn_image)

    for bbox in bboxes:
        x, y, w, h, _class = bbox
        draw.rectangle((x, y, x + w, y + h), outline="red", width=2)

    return np.array(drawn_image)
