import logging
import os

from augmentor.core.base import AugmentorBase, Checker
import augmentor.core.utils as utils


class YOLO(AugmentorBase):
    ALLOWED_IMAGE_FORMATS = (".bmp", ".jpeg", ".jpg", ".png", ".tif", ".tiff", ".webp")
    ALLOWED_LABEL_FORMATS = (".txt",)

    @classmethod
    def scan(cls, path: str, train: bool, val: bool, test: bool) -> tuple[dict, dict]:
        """
        Scan selected subsets in passed *path* of dataset directory depending on the *train*, *val* and *test* flags
        :param path: path to dataset directory
        :param train: whether to scan training subset or not
        :param val: whether to scan validation subset or not
        :param test: whether to scan testing subset or not
        :return: *image_paths* and *label_paths* dictionaries with training, validation or/and testing subsets'
                 corresponding scanned paths
        """
        image_paths = {}
        label_paths = {}

        if train:
            image_paths["train"], label_paths["train"] = cls._scan_subset(path, "train")

        if val:
            image_paths["val"], label_paths["val"] = cls._scan_subset(path, "val")

        if test:
            image_paths["test"], label_paths["test"] = cls._scan_subset(path, "test")

        logging.debug(f"{path} dataset has been scanned")

        return image_paths, label_paths

    @classmethod
    def _scan_subset(cls, path: str, subset: str) -> tuple[list, list]:
        if not (os.path.isdir(path + "/" + subset + "/images") or os.path.isdir(path + "/" + subset + "/labels")):
            raise NotADirectoryError(f"{path}/{subset} is nonexistent or is not a directory")

        images = [path + "/" + subset + "/images/" + image for image in os.listdir(path + "/" + subset + "/images")
                  if image.endswith(cls.ALLOWED_IMAGE_FORMATS)]
        images.sort()

        labels = [path + "/" + subset + "/labels/" + label for label in os.listdir(path + "/" + subset + "/labels")
                  if label.endswith(cls.ALLOWED_LABEL_FORMATS)]
        labels.sort()

        difference = len(images) - len(labels)
        Checker.check_dif(difference, utils.subset_lower(subset))

        images_split = [image.rsplit("/", 1)[-1].rsplit(".", 1)[0] for image in images]
        labels_split = [label.rsplit("/", 1)[-1].rsplit(".", 1)[0] for label in labels]
        labels = [labels[labels_split.index(image_split)] if image_split in labels_split
                  else None for image_split in images_split]

        logging.info(f"{utils.subset_upper(subset)} subset scanned: "
                     f"{len(images)} images | {len(labels) - difference} labels")

        return images, labels

    def _bboxes_read(self, label_path: str):
        logging.debug(f"Reading bounding bboxes from {label_path}")

        bboxes = list()
        height, width, _ = self.image.shape

        if label_path is None:
            self.bboxes = None
        else:
            with open(label_path, "r") as file:
                for line in file:
                    class_, xc, yc, w, h = [int(line.rsplit()[0])] + [float(x) for x in line.rsplit()[1:]]

                    if class_ < 0:
                        logging.warning(f"{label_path} contains bounding box with negative class")

                    if xc < 0 or yc < 0 or w < 0 or h < 0:
                        raise ValueError(f"{label_path} contains bounding box with negative coordinates")

                    w = round(w * width, self.FLOAT_PRECISION)
                    h = round(h * height, self.FLOAT_PRECISION)
                    x = round(xc * width - w / 2, self.FLOAT_PRECISION)
                    y = round(yc * height - h / 2, self.FLOAT_PRECISION)

                    bboxes.append([x, y, w, h, class_])

            self.bboxes = bboxes

    def _bboxes_write(self, label_path: str):
        logging.debug(f"Writing bounding boxes in {label_path}")

        height, width, _ = self.image.shape

        with open(label_path, "w") as file:
            for bbox in self.bboxes:
                x, y, w, h, class_ = bbox

                w = round(w / width, self.FLOAT_PRECISION)
                h = round(h / height, self.FLOAT_PRECISION)
                xc = round(x / width + w / 2, self.FLOAT_PRECISION)
                yc = round(y / height + h / 2, self.FLOAT_PRECISION)

                file.write(f"{class_} {xc} {yc} {w} {h}\n")
