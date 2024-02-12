import numpy as np
import logging
import sys
from abc import ABC, abstractmethod
import os

import tifffile
from PIL import Image


class AugmentorBase(ABC):
    LOGGING_FORMAT = "%(asctime)s - %(levelname)s: %(message)s"
    ALLOWED_AUGMENTATIONS = ("rotate", "flip", "resize", "crop", "saturation",
                             "brightness", "contrast", "blur", "noise")
    FLOAT_PRECISION = 4

    def __init__(self, debug: bool = False, log_path: str = None):
        level = logging.INFO if not debug else logging.DEBUG
        if log_path is None:
            logging.basicConfig(stream=sys.stdout,
                                format=self.LOGGING_FORMAT,
                                level=level)
        elif log_path.endswith(".txt"):
            logging.basicConfig(filename=log_path,
                                filemode="a",
                                format=self.LOGGING_FORMAT,
                                datefmt='%H:%M:%S',
                                level=level)
        else:
            raise ValueError(f"Log path should be in .txt format")

        logging.debug("Augmentor base class object initialized")

        self.load_path = None
        self.save_path = None

        self.image = None
        self.bboxes = None

    def __del__(self):
        logging.debug("Augmentor base class object deleted")
        logging.shutdown()

    def augment(self, *args, **kwargs):
        self.load_path = kwargs.get("load_path", "")
        self.save_path = kwargs.get("save_path", "")

        self._check_paths(self.load_path, self.save_path)

        train = kwargs.get("train", True)
        val = kwargs.get("val", True)
        test = kwargs.get("test", True)

        if not train and not val and not test:
            raise ValueError("No subset chosen for augmentation")

        augmentations = {}
        for i in range(0, len(args), 2):
            self._check_arg(args[i], args[i + 1])
            augmentations[args[i]] = args[i + 1]

        logging.info(f"{self.load_path.rsplit('/')[-1]} dataset chosen for augmentation")
        logging.debug(f"Augmentations: {augmentations}")

        os.system(f"cp -r {self.load_path} {self.save_path}")

        image_paths, label_paths = self.scan(self.load_path, train, val, test)

        logging.info(f"A total amount of "
                     f"{len(image_paths['train']) + len(image_paths['val']) + len(image_paths['test'])} "
                     f"images will be augmented")

        if train:
            self.augment_subset(augmentations, image_paths["train"], label_paths["train"], "train")

        if val:
            self.augment_subset(augmentations, image_paths["val"], label_paths["val"], "val")

        if test:
            self.augment_subset(augmentations, image_paths["test"], label_paths["test"], "test")

        logging.info(f"{self.load_path.rsplit('/')[-1]} dataset has been augmented")

    def augment_subset(self, augmentations: dict, image_paths: list, label_paths: list, subset: str):
        logging.info(f"Augmenting {self._subset_lower(subset)} subset...")

        for augmentation in augmentations:
            count = 0

            for image_path, label_path in zip(image_paths, label_paths):
                self.image_read(image_path)
                self.bboxes_read(label_path)

                getattr(self, f"_AugmentorBase__{augmentation}")(augmentations[augmentation])

                if self.image is not None and self.bboxes is not None:
                    load_image_path = image_path.replace(self.load_path, self.save_path)
                    load_label_path = label_path.replace(self.load_path, self.save_path)

                    self.image_write(f"{load_image_path.rsplit('.', 1)[0]}_{augmentation}_"
                                     f"{count}.{load_image_path.rsplit('.', 1)[1]}")
                    self.bboxes_write(f"{load_label_path.rsplit('.', 1)[0]}_{augmentation}_"
                                      f"{count}.{load_label_path.rsplit('.', 1)[1]}")

                    count += 1

    @classmethod
    @abstractmethod
    def scan(cls, path: str, train: bool, val: bool, test: bool) -> tuple[dict, dict]:
        pass

    def image_read(self, image_path: str):
        logging.debug(f"Reading image {image_path}")

        self.image = tifffile.imread(image_path) if image_path.endswith((".tif", ".tiff")) \
            else np.array(Image.open(image_path))

    def image_write(self, image_path: str):
        logging.debug(f"Writing image {image_path}")

        tifffile.imwrite(image_path, self.image) if image_path.endswith((".tif", ".tiff")) \
            else Image.fromarray(self.image).save(image_path)

    @abstractmethod
    def bboxes_read(self, label_path: str):
        pass

    @abstractmethod
    def bboxes_write(self, label_path: str):
        pass

    @classmethod
    def _check_arg(cls, augmentation: str, argument: int or float or tuple):
        logging.debug(f"Checking argument {argument}...")

        if augmentation not in cls.ALLOWED_AUGMENTATIONS:
            raise ValueError(f"Unknown augmentation {augmentation}")

        if augmentation in (cls.ALLOWED_AUGMENTATIONS[0], cls.ALLOWED_AUGMENTATIONS[1], cls.ALLOWED_AUGMENTATIONS[4],
                            cls.ALLOWED_AUGMENTATIONS[5], cls.ALLOWED_AUGMENTATIONS[6], cls.ALLOWED_AUGMENTATIONS[7]):
            if type(argument) is not int:
                raise TypeError(f"For {augmentation} augmentation additional argument should be integer")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[0] and argument not in (-270, -180, 90, 90, 180, 270):
                raise ValueError(f"Cannot rotate by angle {argument}")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[1] and argument not in (-1, 0, 1):
                raise ValueError(f"Cannot flip by axis {argument}")

            if (augmentation in (cls.ALLOWED_AUGMENTATIONS[4], cls.ALLOWED_AUGMENTATIONS[5],
                                 cls.ALLOWED_AUGMENTATIONS[6]) and 0 > argument > 255):
                raise ValueError(f"Level of {augmentation} {argument} is out of range (0..255)")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[7] and 0 > argument > 15:
                raise ValueError(f"Radius of blur {argument} is out of range (0..15)")

        elif augmentation in (cls.ALLOWED_AUGMENTATIONS[2], cls.ALLOWED_AUGMENTATIONS[8]):
            if type(argument) is not float:
                raise TypeError(f"For {augmentation} augmentation additional argument should be float")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[2] and 0. >= argument > 4.:
                raise ValueError(f"Resize ratio {argument} is out of range (0.0..4.0)")

            if augmentation is cls.ALLOWED_AUGMENTATIONS[8] and 0. >= argument > 1.:
                raise ValueError(f"Noise ratio {argument} is out of range (0.0..1.0)")

        elif augmentation is cls.ALLOWED_AUGMENTATIONS[3]:
            if type(argument) is not tuple or len(argument) != 4 or not all(type(coord) is int for coord in argument):
                raise TypeError("For crop augmentation additional argument should be a tuple of 4 integers")

            if (augmentation is cls.ALLOWED_AUGMENTATIONS[3] and
                    argument[0] < 0 or argument[1] < 0 or argument[2] <= 0 or argument[3] <= 0):
                raise ValueError(f"Cannot crop with coordinates {argument}")

    @staticmethod
    def _check_paths(load_path: str, save_path: str):
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
    def _check_dif(dif: int, subset_lower: str):
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
    def _subset_upper(subset: str) -> str:
        return "Training" if subset == "train" else "Validation" if subset == "val" else "Testing"

    @staticmethod
    def _subset_lower(subset: str) -> str:
        return "training" if subset == "train" else "validation" if subset == "val" else "testing"

    def __rotate(self, angle: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __flip(self, axis: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __resize(self, ratio: float):
        self.image = self.image
        self.bboxes = self.bboxes

    def __crop(self, coordinates: tuple[int, int, int, int]):
        self.image = self.image
        self.bboxes = self.bboxes

    def __saturation(self, level: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __brightness(self, level: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __contrast(self, level: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __blur(self, radius: int):
        self.image = self.image
        self.bboxes = self.bboxes

    def __noise(self, ratio: float):
        self.image = self.image
        self.bboxes = self.bboxes
