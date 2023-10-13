#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageIO.h"
#include "crypto.h"

// Code: ...
// Remplacez les "..." par le code à 8 chiffres trouvé dans l'une des images fournies
// Ne modifiez rien d'autre sur ces trois lignes de commentaires.

Image* mapImage(int nbImg, Image **images, Pixel (*f)(int nb, Pixel*),
        int newImage) {

    // temp Image* p = getImagePixel(images[0], getNbRows(images[0]), getNbRows(images[0]));
    Pixel* p = malloc(sizeof(Pixel));
    if (f(nbImg, p).r == 1)
        return images[newImage];

    return NULL;

}

Image* decrypt(Image *img) {

    return img;
    // p2 = (p1 % 8) * 32

}

void encrypt(Image *img1, Image *img2) {

    printf("%d", (int) getNbRows(img1));
    printf("\nET : ");
    printf("%d", (int) getNbRows(img2));

    // p1 = p1 - p1 % 8 + p2 / 32

}
