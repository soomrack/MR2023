import numpy as np
from PIL import Image

from augmentor.core.base import Checker


def rotate(image: np.ndarray, bboxes: list, angle: int) -> tuple[np.ndarray, list]:
    """
    Rotate image and bounding boxes by *-270*, *-180*, *-90*, *90*, *180* or *270* degrees counter-clockwise. If angle
    is *180* or *-180* the image is just flipped along both x and y axes instead
    :param image: image as NumPy array
    :param bboxes: bounding boxes list of (x, y, w, h, class)
    :param angle: angle to rotate by
    :return: rotated image and bounding boxes list
    """
    if angle == 180 or angle == -180:
        return flip(image, bboxes, -1)

    rotated_image = np.rot90(image, k=1)
    rotated_bboxes = [[y, image.shape[1] - x - w, h, w, class_] for [x, y, w, h, class_] in bboxes]

    if angle == 270 or angle == -90:
        return flip(rotated_image, rotated_bboxes, 1)

    return rotated_image, rotated_bboxes


def flip(image: np.ndarray, bboxes: list, axis: int) -> tuple[np.ndarray, list]:
    """
    Flip image and bounding boxes along given axis. *-1* stands for flipping along both x and y axes, *0* stands for
    flipping along x-axis, *1* stands for flipping along y-axis
    :param image: image as NumPy array
    :param bboxes: bounding boxes list of (x, y, w, h, class)
    :param axis: axis to flip along
    :return: flipped image and bounding boxes list
    """
    height, width, _ = image.shape

    if axis == 0:
        flipped_image = np.flip(image, 0)
        flipped_bboxes = [[x, height - y - h, w, h, class_] for [x, y, w, h, class_] in bboxes]

    elif axis == 1:
        flipped_image = np.flip(image, 1)
        flipped_bboxes = [[width - x - w, y, w, h, class_] for [x, y, w, h, class_] in bboxes]

    else:
        flipped_image = np.flip(image, (0, 1))
        flipped_bboxes = [[width - x - w, height - y - h, w, h, class_] for [x, y, w, h, class_] in bboxes]

    return flipped_image, flipped_bboxes


def resize(image: np.ndarray, bboxes: list, ratio: float) -> tuple[np.ndarray, list]:
    """
    Resize the image and bounding boxes to the given ratio between 0.0 and 2.0
    :param image: image as NumPy array
    :param bboxes: bounding boxes list of (x, y, w, h, class)
    :param ratio: resize ratio
    :return: resized image and bounding boxes list
    """
    height, width, _ = image.shape

    resized_image = np.array(Image.fromarray(image).resize((int(width * ratio), int(height * ratio))))
    resized_bboxes = [[ratio * x, ratio * y, ratio * w, ratio * h, class_] for [x, y, w, h, class_] in bboxes]

    return resized_image, resized_bboxes


def crop(image: np.ndarray, bboxes: list, coordinates: tuple[int, int, int, int]) -> tuple[np.ndarray, list]:
    """
    Crop the image and bounding boxes using given (x, y, w, h) coordinates. *x*, *y* stand for the top-left corner
    coordinates of the cropped zone, whereas *w*, *h* stand for its width and height. Bounding boxes get into the
    resulting list if they are within the cropped zone at least partially. Each crop augmentation is followed by an
    image shape checkout through *Checker* abstract class
    :param image: image as NumPy array
    :param bboxes: bounding boxes list of (x, y, w, h, class)
    :param coordinates: cropped zone coordinates
    :return: cropped image and bounding boxes list
    """
    Checker.check_shape(image.shape, coordinates)

    x_crop, y_crop, w_crop, h_crop = coordinates

    cropped_image = image[y_crop:y_crop + h_crop, x_crop:x_crop + w_crop]
    cropped_bboxes = list()

    for bbox in bboxes:
        x, y, w, h, class_ = bbox

        if x >= x_crop and x + w <= x_crop + w_crop:
            bbox[0] -= x_crop

        if x < x_crop and x + w <= x_crop + w_crop:
            bbox[0] = 0
            bbox[2] += x - x_crop

        if x >= x_crop and x + w > x_crop + w_crop:
            bbox[0] -= x_crop
            bbox[2] = x_crop + w_crop - x

        if y >= y_crop and y + h <= y_crop + h_crop:
            bbox[1] -= y_crop

        if y < y_crop and y + h <= y_crop + h_crop:
            bbox[1] = 0
            bbox[3] += y - y_crop

        if y >= y_crop and y + h > y_crop + h_crop:
            bbox[1] -= y_crop
            bbox[3] = y_crop + h_crop - y

        if (bbox[0] < 0 or bbox[1] < 0 or bbox[2] < 0 or bbox[3] < 0
                or bbox[0] + bbox[2] > w_crop or bbox[1] + bbox[3] > h_crop):
            continue

        cropped_bboxes.append(bbox)

    return cropped_image, cropped_bboxes
