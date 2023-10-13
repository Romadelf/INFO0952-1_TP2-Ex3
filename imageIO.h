#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <stdlib.h>

// Opaque structure representing an image
typedef struct Image_t Image;

// Structure representing a pixel
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/**
 * @brief Create a Image object
 *
 * @param nb_rows the number of rows of the image
 * @param nb_col the number of columns of the image
 * @return Image* the created image
 */
Image* createImage(size_t nb_rows, size_t nb_col);

/**
 * @brief Free the memory allocated for the image
 *
 * @param img the image to free
 */
void freeImage(Image *img);

/**
 * @brief Get the image pixel at the given position
 *
 * @param img the image
 * @param i the row index
 * @param j the column index
 * @return Pixel the pixel at the given position
 */
Pixel getImagePixel(Image *img, size_t i, size_t j);

/**
 * @brief Set the image pixel at the given position
 *
 * @param img the image
 * @param i the row index
 * @param j the column index
 * @param p the new value of the pixel
 */
void setImagePixel(Image *img, size_t i, size_t j, Pixel p);

/**
 * @brief Read an image from a file
 *
 * @param filename the name of the file
 * @return Image* the image read from the file
 */
Image* readImage(const char *filename);

/**
 * @brief Write an image to a file
 *
 * @param filename the name of the file
 * @param img the image to write
 */
void writeImage(const char *filename, Image *img);

/**
 * @brief Get the number of rows of the image
 *
 * @param img the image
 * @return size_t the number of rows of the image
 */
size_t getNbRows(Image *img);

/**
 * @brief Get the number of columns of the image
 *
 * @param img the image
 * @return size_t the number of columns of the image
 */
size_t getNbColumns(Image *img);

#endif
