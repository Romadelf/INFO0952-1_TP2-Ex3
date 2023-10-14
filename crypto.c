#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageIO.h"
#include "crypto.h"

// Code: 43664815
// Remplacez les "..." par le code à 8 chiffres trouvé dans l'une des images fournies
// Ne modifiez rien d'autre sur ces trois lignes de commentaires.

Image* mapImage(int nbImg, Image **images, Pixel (*f)(int nb, Pixel*),
        int newImage) {

    if (nbImg <= 0)
        return NULL;

    size_t rows = getNbRows(images[0]);
    size_t cols = getNbColumns(images[0]);
    Image *img = newImage == 1 ? createImage(rows, cols) : images[0];
    int n = sizeof(images);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) {

            Pixel *p = malloc(n * sizeof(Pixel));
            for (int k = 0; k < n; k++)
                p[k] = getImagePixel(images[k], i, j);

            Pixel result = f(n, p);
            setImagePixel(img, i, j, result);
        }

    return img;

}

Image* decrypt(Image *img) {

    size_t rows = getNbRows(img);
    size_t cols = getNbColumns(img);
    Image *img2 = createImage(rows, cols);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) {
            Pixel p = getImagePixel(img, i, j);

            p.r = p.r % 8 * 32;
            p.g = p.g % 8 * 32;
            p.b = p.b % 8 * 32;

            setImagePixel(img2, i, j, p);
        }

    return img2;

}

void encrypt(Image *img1, Image *img2) {

    size_t rows = getNbRows(img1);
    size_t cols = getNbColumns(img1);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) {
            Pixel p1 = getImagePixel(img1, i, j);
            Pixel p2 = getImagePixel(img2, i, j);

            p1.r += -p1.r % 8 + p2.r / 32;
            p1.g += -p1.g % 8 + p2.g / 32;
            p1.b += -p1.b % 8 + p2.b / 32;

            setImagePixel(img1, i, j, p1);
        }

}
