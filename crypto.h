#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageIO.h"

/**
 * @brief Create a new image by applying a function to the pixels of several
 * images
 *
 * @param nbImg the number of images
 * @param images the array of images
 * @param f the function to apply
 * @param newImage if 1, create a new image, otherwise modify the first image
 * @return Image* the new image
 */
Image *mapImage(int nbImg, Image **images, Pixel (*f)(int nb, Pixel *), int newImage);

/**
 * @brief Decrypt an image
 *
 * @param img the image to decrypt
 * @return Image* the decrypted hidden image
 */
Image *decrypt(Image *img);

/**
 * @brief Encrypt an image
 *
 * @param img1 the image to encrypt
 * @param img2 the image to hide
 */
void encrypt(Image *img1, Image *img2);

#endif
