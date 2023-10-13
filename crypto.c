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

    // temp Image* p = getImagePixel(images[0], getNbRows(images[0]), getNbRows(images[0]));
    Pixel *p = malloc(sizeof(Pixel));
    if (f(nbImg, p).r == 1)
        return images[newImage];

    return NULL;

}

Image* decrypt(Image *img) {

    size_t rows = getNbRows(img);
    size_t cols = getNbColumns(img);
    Image *img2 = createImage(rows, cols);

    for (size_t i = 0; i < cols; i++)
        for (size_t j = 0; j < rows; j++) {
            Pixel p = getImagePixel(img, j, i);

            p.r = p.r % 8 * 32;
            p.g = p.g % 8 * 32;
            p.b = p.b % 8 * 32;

            setImagePixel(img2, j, i, p);
        }

    return img2;

}

/** TODO : Les images sont supposées de même taille */
void encrypt(Image *img1, Image *img2) {

    size_t rows = getNbRows(img1);
    size_t cols = getNbColumns(img1);

    for (size_t i = 0; i < cols; i++)
        for (size_t j = 0; j < rows; j++) {
            Pixel p1 = getImagePixel(img1, j, i);
            Pixel p2 = getImagePixel(img2, j, i);

            p1.r -= p1.r % 8 + p2.r / 32;
            p1.g -= p1.g % 8 + p2.g / 32;
            p1.b -= p1.b % 8 + p2.b / 32;

            setImagePixel(img1, j, i, p1);
        }

}
