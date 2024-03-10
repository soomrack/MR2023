from .geometric import rotate, flip, resize, crop
from .photometric import saturation, contrast, brightness, blur, noise

GEOMETRIC_AUGMENTATIONS = ("rotate", "flip", "resize", "crop")
PHOTOMETRIC_AUGMENTATIONS = ("saturation", "contrast", "brightness", "blur", "noise")
