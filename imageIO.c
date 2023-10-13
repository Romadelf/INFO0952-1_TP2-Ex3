#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "imageIO.h"

struct Image_t
{
	size_t nb_rows;
	size_t nb_columns;
	Pixel **content;
};

Image *initImage(size_t nb_rows, size_t nb_col, unsigned char *red, unsigned char *green, unsigned char *blue);

Image *createImage(size_t nb_rows, size_t nb_col)
{
	Pixel **content = (Pixel **)malloc(nb_rows * sizeof(Pixel *));
	for (size_t i = 0; i < nb_rows; i++)
		content[i] = (Pixel *)malloc(nb_col * sizeof(Pixel));
	Image *img = malloc(sizeof(Image));
	img->nb_rows = nb_rows;
	img->nb_columns = nb_col;
	img->content = content;
	return img;
}

void freeImage(Image *img)
{
	for (size_t i = 0; i < img->nb_rows; i++)
		free(img->content[i]);
	free(img->content);
	free(img);
}

Pixel getImagePixel(Image *img, size_t i, size_t j)
{
	if (i < 0 || i >= img->nb_rows || j < 0 || j >= img->nb_columns)
		exit(-1);
	else
		return img->content[i][j];
}

void setImagePixel(Image *img, size_t i, size_t j, Pixel p)
{
	if (i < 0 || i >= img->nb_rows || j < 0 || j >= img->nb_columns)
		exit(-1);
	else
		img->content[i][j] = p;
}

size_t getNbRows(Image *img)
{
	return img->nb_rows;
}

size_t getNbColumns(Image *img)
{
	return img->nb_columns;
}

Image *initImage(size_t nb_rows, size_t nb_col, unsigned char *red, unsigned char *green, unsigned char *blue)
{
	Image *img = createImage(nb_rows, nb_col);
	for (size_t i = 0; i < nb_rows; i++)
	{
		for (size_t j = 0; j < nb_col; j++)
		{
			img->content[i][j].r = red[nb_col * i + j];
			img->content[i][j].g = green[nb_col * i + j];
			img->content[i][j].b = blue[nb_col * i + j];
		}
	}
	return img;
}

Image *readImage(const char *filename)
{
	FILE *fIn = fopen(filename, "r");
	if (fIn == NULL)
	{
		printf("File does not exist.\n");
		exit(-1);
	}

	unsigned char byte[54];
	for (size_t i = 0; i < 54; i++)
	{
		byte[i] = getc(fIn);
	}
	int img_height = *(int *)&byte[18];
	int img_width = *(int *)&byte[22];

	bool reverse_width = img_width < 0;

	img_width = abs(img_width);

	size_t size = img_height * img_width;
	unsigned char red[size];
	unsigned char blue[size];
	unsigned char green[size];

	int i;
	for (int h = 0; h < img_height; h++)
	{
		for (int w = 0; w < img_width; w++)
		{
			if (reverse_width)
				// i = h * img_width + (img_width - w - 1);
				i = (img_height - h - 1) * img_width + w;

			else
				i = h * img_width + w;

			blue[i] = getc(fIn);
			green[i] = getc(fIn);
			red[i] = getc(fIn);
		}
	}
	fclose(fIn);

	return initImage(img_height, img_width, red, green, blue);
}

void writeImage(const char *filename, Image *img)
{
	FILE *fOut = fopen(filename, "w+");
	unsigned char basic[56] = {66, 77, 54, 0, 12, 0, 0, 0, 0, 0, 54, 0, 0, 0, 40, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 24, 0, 0, 0, 0, 0, 0, 0, 12, 0, 206, 14, 0, 0, 216, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	basic[18] = (unsigned char)img->nb_rows;
	basic[22] = (unsigned char)img->nb_columns;
	fwrite(basic, sizeof(unsigned char), 54, fOut);
	for (size_t i = 0; i < img->nb_rows; i++)
	{
		for (size_t j = 0; j < img->nb_columns; j++)
		{
			putc(img->content[i][j].b, fOut);
			putc(img->content[i][j].g, fOut);
			putc(img->content[i][j].r, fOut);
		}
	}
	fclose(fOut);
}
