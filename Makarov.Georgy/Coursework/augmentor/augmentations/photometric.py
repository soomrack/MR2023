import numpy as np
from PIL import Image, ImageEnhance


def saturation(image: np.ndarray, factor: float) -> np.ndarray:
    """
    Adjust image saturation using a ImageEnhance PIL submodule. Factor should be between 0.0 and 2.0. *0.0* will return
    black and white image, *1.0* will leave it unchanged and *2.0* will increase its saturation to a noticeable extent
    :param image: image as NumPy array
    :param factor: saturation factor
    :return: image with adjusted saturation
    """
    return np.array(ImageEnhance.Color(Image.fromarray(image)).enhance(factor))


def contrast(image: np.ndarray, factor: float) -> np.ndarray:
    """
    Adjust image contrat using a ImageEnhance PIL submodule. Factor should be between 0.0 and 2.0. *0.0* will make the
    image solid grey, *1.0* will leave it unchanged and *2.0* will increase its contrast to a noticeable extent
    :param image: image as NumPy array
    :param factor: contrast factor
    :return: image with adjusted contrast
    """
    return np.array(ImageEnhance.Contrast(Image.fromarray(image)).enhance(factor))


def brightness(image: np.ndarray, factor: float) -> np.ndarray:
    """
    Adjust image brightness using a ImageEnhance PIL submodule. Factor should be between 0.0 and 2.0. *0.0* will return
    blackened image, *1.0* will leave it unchanged and *2.0* will increase its brightness to a noticeable extent
    :param image: image as NumPy array
    :param factor: saturation factor
    :return: image with adjusted saturation
    """
    return np.array(ImageEnhance.Brightness(Image.fromarray(image)).enhance(factor))


def blur(image: np.ndarray, sigma: float) -> np.ndarray:
    """
    Blur image using Gaussian blur through x and y along-axes convolutions. The sigma parameter is used to adjust the
    strength of the blurring, it should be between 0.0 and 2.0. The kernel is automatically calculated with size 3
    :param image: image as NumPy array
    :param sigma: standard deviation of the Gaussian distribution
    :return: image with applied Gaussian blur
    """
    kernel = np.exp(-0.5 * (np.arange(-(3 // 2), 3 // 2 + 1) / sigma) ** 2)
    kernel = kernel / np.sum(kernel)

    blurred_image = image.astype(np.float32) / 255.
    blurred_image = np.apply_along_axis(lambda x: np.convolve(x, kernel, mode='same'), 0, blurred_image)
    blurred_image = np.apply_along_axis(lambda y: np.convolve(y, kernel, mode='same'), 1, blurred_image)
    blurred_image = (blurred_image * 255.).astype(np.uint8)

    return blurred_image


def noise(image: np.ndarray, sigma: float) -> np.ndarray:
    """
    Add Gaussian noise to the image. The sigma parameter is used to adjust the strength of the noising, it should be
    between 0.0 and 2.0. The mean grey value in the probability density function is equal to 0 during calculation
    :param image: image as NumPy array
    :param sigma: standard deviation of the Gaussian distribution
    :return: image with applied Gaussian noise
    """
    gaussian_noise = np.random.normal(0, sigma, image.shape)

    noised_image = image.astype(np.float32) / 255.
    noised_image = np.clip(noised_image + gaussian_noise, 0., 1.)
    noised_image = (noised_image * 255.).astype(np.uint8)

    return noised_image
