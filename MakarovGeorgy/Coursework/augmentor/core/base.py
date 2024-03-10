from abc import ABC, abstractmethod
import logging
import sys
import os

import numpy as np
from PIL import Image

import augmentor


class AugmentorBase(ABC):
    LOGGING_FORMAT = "%(asctime)s %(levelname)s - %(message)s"
    FLOAT_PRECISION = 4

    def __init__(self, debug: bool = False, log_path: str = None):
        level = logging.INFO if not debug else logging.DEBUG
        if log_path is None:
            logging.basicConfig(stream=sys.stdout,
                                format=self.LOGGING_FORMAT,
                                datefmt='%H:%M:%S',
                                level=level)
        elif log_path.endswith(".txt"):
            Checker.check_log(log_path)
            logging.basicConfig(filename=log_path,
                                filemode="a",
                                format=self.LOGGING_FORMAT,
                                datefmt='%H:%M:%S',
                                level=level)
        else:
            raise ValueError(f"Log path should be with .txt extension")

        logging.debug("Augmentor class object initialized")

        self.load_path = None
        self.save_path = None

        self.image = None
        self.bboxes = None

    def __del__(self):
        logging.debug("Augmentor class object deleted")
        logging.shutdown()

    def augment(self, *args, **kwargs):
        """
        Augment dataset by modifying images and labels in selected subsets with given augmentation pipeline in arguments
        using *load_path* and *save_path* paths, *train*, *val* and *test* flags from keyword arguments. In the process,
        the original dataset gets copied to *save_path* and augmented images and bounding boxes get saved along with
        unique filenames - *original-name_augmentation+id.original-extension*
        :param args: each augmentation in the pipeline should be passed as 2 consequent arguments - augmentation name
                     and corresponding value (e.g. *"rotate", 90* to rotate images by angle 90)
        :param kwargs: *load_path* to directory with dataset for augmentation, *save_path* to nonexistent directory
                       where augmented dataset will be created and saved, *train*, *val* and *test* flags to indicate
                       which subsets are to be augmented
        """
        self.load_path = kwargs.get("load_path", "")
        self.save_path = kwargs.get("save_path", "")

        Checker.check_paths(self.load_path, self.save_path)

        train = kwargs.get("train", True)
        val = kwargs.get("val", True)
        test = kwargs.get("test", True)

        if not train and not val and not test:
            raise ValueError("No subset chosen for augmentation")

        augmentations = {args[i]: [] for i in range(0, len(args), 2)}
        for i in range(0, len(args), 2):
            Checker.check_args(args[i], args[i + 1])
            augmentations[args[i]].append(args[i + 1])

        logging.info(f"{self.load_path.rsplit('/')[-1]} dataset chosen for augmentation")
        logging.debug(f"Augmentations: {augmentations}")

        os.system(f"cp -r {self.load_path} {self.save_path}")
        os.system(f"find {self.save_path} -name '*.cache' -type f -delete")

        image_paths, label_paths = self.scan(self.load_path, train, val, test)

        logging.info(f"A total amount of "
                     f"{len(image_paths['train']) + len(image_paths['val']) + len(image_paths['test'])} "
                     f"images will be augmented")

        if train:
            self._augment_subset(augmentations, image_paths["train"], label_paths["train"], "train")

        if val:
            self._augment_subset(augmentations, image_paths["val"], label_paths["val"], "val")

        if test:
            self._augment_subset(augmentations, image_paths["test"], label_paths["test"], "test")

        logging.info(f"{self.load_path.rsplit('/')[-1]} dataset has been augmented")

    def _augment_subset(self, augmentations: dict, image_paths: list, label_paths: list, subset: str):
        logging.info(f"Augmenting {augmentor.utils.subset_lower(subset)} subset...")

        for augmentation in augmentations:
            count = 0

            for value in augmentations[augmentation]:
                for image_path, label_path in zip(image_paths, label_paths):
                    self._image_read(image_path)
                    self._bboxes_read(label_path)

                    if augmentation in augmentor.augmentations.GEOMETRIC_AUGMENTATIONS:
                        self.image, self.bboxes = (getattr(augmentor.augmentations.geometric, f"{augmentation}")
                                                   (self.image, self.bboxes, value))
                    elif augmentation in augmentor.augmentations.PHOTOMETRIC_AUGMENTATIONS:
                        self.image = (getattr(augmentor.augmentations.photometric, f"{augmentation}")
                                      (self.image, value))

                    if self.image is not None and self.bboxes is not None:
                        load_image_path = image_path.replace(self.load_path, self.save_path)
                        load_label_path = label_path.replace(self.load_path, self.save_path)

                        self._image_write(f"{load_image_path.rsplit('.', 1)[0]}_{augmentation}"
                                          f"{count}.{load_image_path.rsplit('.', 1)[1]}")
                        self._bboxes_write(f"{load_label_path.rsplit('.', 1)[0]}_{augmentation}"
                                           f"{count}.{load_label_path.rsplit('.', 1)[1]}")

                count += 1

    @classmethod
    @abstractmethod
    def scan(cls, path: str, train: bool, val: bool, test: bool) -> tuple[dict, dict]:
        pass

    @classmethod
    @abstractmethod
    def _scan_subset(cls, path: str, subset: str) -> tuple[list, list]:
        pass

    def _image_read(self, image_path: str):
        logging.debug(f"Reading image {image_path}")

        self.image = np.array(Image.open(image_path).convert("RGB"))

    def _image_write(self, image_path: str):
        logging.debug(f"Writing image {image_path}")

        Image.fromarray(self.image, "RGB").save(image_path)

    @abstractmethod
    def _bboxes_read(self, label_path: str):
        pass

    @abstractmethod
    def _bboxes_write(self, label_path: str):
        pass


class Checker(ABC):
    ALLOWED_AUGMENTATIONS = ("rotate", "flip", "resize", "crop",
                             "saturation", "brightness", "contrast", "blur", "noise")

    @staticmethod
    def check_log(log_path: str):
        if not os.path.isabs(log_path):
            raise ValueError(f"{log_path} is not an absolute path")

        if os.path.exists(log_path):
            raise FileExistsError(f"{log_path} already exists")

    @classmethod
    def check_args(cls, augmentation: str, value: int or float or tuple[int, int, int, int]):
        logging.debug(f"Checking argument {value}...")

        if augmentation not in cls.ALLOWED_AUGMENTATIONS:
            raise ValueError(f"Unknown augmentation {augmentation}")

        if augmentation in (cls.ALLOWED_AUGMENTATIONS[0], cls.ALLOWED_AUGMENTATIONS[1]):
            if type(value) is not int:
                raise TypeError(f"For {augmentation} augmentation value should be integer")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[0] and value not in (-270, -180, -90, 90, 180, 270):
                raise ValueError(f"Cannot rotate by angle {value}")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[1] and value not in (-1, 0, 1):
                raise ValueError(f"Cannot flip by axis {value}")

        elif augmentation in (cls.ALLOWED_AUGMENTATIONS[2], cls.ALLOWED_AUGMENTATIONS[8]):
            if type(value) is not float:
                raise TypeError(f"For {augmentation} augmentation value should be float")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[2] and 0. >= value > 2.:
                raise ValueError(f"For resize augmentation ratio should be between 0.0 and 2.0")

            if augmentation in (cls.ALLOWED_AUGMENTATIONS[4], cls.ALLOWED_AUGMENTATIONS[5],
                                cls.ALLOWED_AUGMENTATIONS[6]) and 0. >= value > 2.:
                raise ValueError(f"For {augmentation} augmentation factor should be between 0.0 and 2.0")

            if augmentation in (cls.ALLOWED_AUGMENTATIONS[7], cls.ALLOWED_AUGMENTATIONS[8]) and 0. >= value > 2.:
                raise ValueError(f"For {augmentation} augmentation sigma should be between 0.0 and 2.0")

        elif augmentation is cls.ALLOWED_AUGMENTATIONS[3]:
            if type(value) is not tuple or len(value) != 4 or not all(type(coord) is int for coord in value):
                raise TypeError("For crop augmentation value should be a tuple of 4 integers")

            if (augmentation is cls.ALLOWED_AUGMENTATIONS[3] and
                    value[0] < 0 or value[1] < 0 or value[2] <= 0 or value[3] <= 0):
                raise ValueError(f"Cannot crop with coordinates {value}")

    @staticmethod
    def check_paths(load_path: str, save_path: str):
        logging.debug(f"Checking load path {load_path} and save path {save_path}...")

        if load_path == "":
            raise ValueError("Keyword argument load_path is required")
        if save_path == "":
            raise ValueError("Keyword argument save_path is required")

        if not os.path.isdir(load_path):
            raise NotADirectoryError(f"{load_path} directory is nonexistent")
        if os.path.isdir(save_path):
            raise IsADirectoryError(f"{save_path} directory already exists")

    @staticmethod
    def check_dif(dif: int, subset_lower: str):
        logging.debug("Checking difference between images and labels...")

        if dif == 1:
            logging.warning(f"{subset_lower} label is missing")
        elif dif > 1:
            logging.warning(f"{dif} {subset_lower} labels are missing")
        elif dif == -1:
            logging.warning(f"Redundant {subset_lower} label has been found")
        elif dif < -1:
            logging.warning(f"{dif} redundant {subset_lower} labels have been found")

    @staticmethod
    def check_shape(shape: [int, int, int], coordinates: tuple[int, int, int, int]):
        height, width, _ = shape

        if coordinates[0] + coordinates[2] > width:
            raise ValueError("Crop zone exceeds processing image width")

        if coordinates[1] + coordinates[3] > height:
            raise ValueError("Crop zone exceeds processing image height")
