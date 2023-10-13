#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crypto.h"
#include "imageIO.h"

// encryption :
// ./crypto images/airplane.bmp images/pepper.bmp images/ici.bmp
//
// decryption :
// ./crypto images/ici.bmp images/ici2.bmp

int main(int argc, char const *argv[]) {
    if (argc != 4 && argc != 3) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr,
                "For decryption: %s filename_encrypted_image filename_decrypted_image\n",
                argv[0]);
        fprintf(stderr,
                "For encryption: %s filename_source_image1 filename_source_image2 filename_encrypted_image\n",
                argv[0]);
        return 1;
    }

    if (argc == 4) { // on encrypte
        Image *img1 = readImage(argv[1]);
        Image *img2 = readImage(argv[2]);
        encrypt(img1, img2);
        writeImage(argv[3], img1);
        freeImage(img1);
        freeImage(img2);
    } else { // on decrypte
        Image *img1 = readImage(argv[1]);
        Image *decryptimg1 = decrypt(img1);
        writeImage(argv[2], decryptimg1);
        freeImage(img1);
        freeImage(decryptimg1);
    }
}
