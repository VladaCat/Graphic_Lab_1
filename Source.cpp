#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
typedef int FXPT2DOT30;
using namespace std;
typedef struct {
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
	CIEXYZ  ciexyzRed;
	CIEXYZ  ciexyzGreen;
	CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct
{
	unsigned int    bfType;
	unsigned long   bfSize;
	unsigned int    bfReserved1;
	unsigned int    bfReserved2;
	unsigned long   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
	unsigned int    biSize;
	int             biWidth;
	int             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;
	unsigned int   biRedMask;
	unsigned int   biGreenMask;
	unsigned int   biBlueMask;
	unsigned int   biAlphaMask;
	unsigned int   biCSType;
	CIEXYZTRIPLE   biEndpoints;
	unsigned int   biGammaRed;
	unsigned int   biGammaGreen;
	unsigned int   biGammaBlue;
	unsigned int   biIntent;
	unsigned int   biProfileData;
	unsigned int   biProfileSize;
	unsigned int   biReserved;
} BITMAPINFOHEADER;

typedef struct
{
	int   rgbBlue;
	int   rgbGreen;
	int   rgbRed;
	int   rgbReserved;
} RGBQUAD;


static unsigned short read_u16(FILE* fp);
static unsigned int   read_u32(FILE* fp);
static int            read_s32(FILE* fp);

static void write_u16(unsigned short input, FILE* fp);
static void write_u32(unsigned int input, FILE* fp);
static void write_s32(int input, FILE* fp);
int sort(int** mas, int n);
#endif // MAIN_H_INCLUDEDs

int main()
{
	printf("Start\n");
	FILE* pFile = fopen("C:/photo/cat.bmp", "rb");

	BITMAPFILEHEADER header;
	header.bfType = read_u16(pFile);
	header.bfSize = read_u32(pFile);
	header.bfReserved1 = read_u16(pFile);
	header.bfReserved2 = read_u16(pFile);
	header.bfOffBits = read_u32(pFile);
	BITMAPINFOHEADER bmiHeader;

	bmiHeader.biSize = read_u32(pFile);
	if (bmiHeader.biSize >= 40)
	{
		bmiHeader.biWidth = read_u32(pFile);
		bmiHeader.biHeight = read_u32(pFile);
		bmiHeader.biPlanes = read_u16(pFile);
		bmiHeader.biBitCount = read_u16(pFile);
		bmiHeader.biCompression = read_u32(pFile);
		bmiHeader.biSizeImage = read_u32(pFile);
		bmiHeader.biXPelsPerMeter = read_s32(pFile);
		bmiHeader.biYPelsPerMeter = read_s32(pFile);
		bmiHeader.biClrUsed = read_u32(pFile);
		bmiHeader.biClrImportant = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 52)
	{
		bmiHeader.biRedMask = read_u32(pFile);
		bmiHeader.biGreenMask = read_u32(pFile);
		bmiHeader.biBlueMask = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 56)
	{
		bmiHeader.biAlphaMask = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 108)
	{
		bmiHeader.biCSType = read_u32(pFile);
		fread(&bmiHeader.biEndpoints, 36, 1, pFile);
		bmiHeader.biGammaRed = read_u32(pFile);
		bmiHeader.biGammaGreen = read_u32(pFile);
		bmiHeader.biGammaBlue = read_u32(pFile);
	}
	if (bmiHeader.biSize >= 124)
	{
		bmiHeader.biIntent = read_u32(pFile);
		bmiHeader.biProfileData = read_u32(pFile);
		bmiHeader.biProfileSize = read_u32(pFile);
		bmiHeader.biReserved = read_u32(pFile);
	}
	cout << "Width:" << bmiHeader.biWidth << "  " << "Height:" << bmiHeader.biHeight << endl;
	cout << "BitCount:" << bmiHeader.biBitCount << endl;
	cout << "ColorUsed:" << bmiHeader.biClrUsed << endl;

	RGBQUAD** pixels = new RGBQUAD * [bmiHeader.biHeight];

	for (int i = 0; i < bmiHeader.biHeight; i++)
	{
		pixels[i] = new RGBQUAD[bmiHeader.biWidth];

	}
	for (int i = 0; i < bmiHeader.biHeight; i++)
		for (int j = 0; j < bmiHeader.biWidth; j++)
		{
			pixels[i][j].rgbBlue = getc(pFile);
			pixels[i][j].rgbGreen = getc(pFile);
			pixels[i][j].rgbRed = getc(pFile);
			pixels[i][j].rgbReserved = getc(pFile);


		}

	fclose(pFile);
	FILE* test1 = fopen("C:/photo/cat.bmp", "w+b");

	write_u16(header.bfType, test1);
	write_u32(header.bfSize, test1);
	write_u16(header.bfReserved1, test1);
	write_u16(header.bfReserved2, test1);
	write_u32(header.bfOffBits, test1);

	write_u32(bmiHeader.biSize, test1);
	if (bmiHeader.biSize >= 40)
	{
		write_s32(bmiHeader.biWidth, test1);
		write_s32(bmiHeader.biHeight, test1);
		write_u16(bmiHeader.biPlanes, test1);
		write_u16(bmiHeader.biBitCount, test1);
		write_u32(bmiHeader.biCompression, test1);
		write_u32(bmiHeader.biSizeImage, test1);
		write_s32(bmiHeader.biXPelsPerMeter, test1);
		write_s32(bmiHeader.biYPelsPerMeter, test1);
		write_u32(bmiHeader.biClrUsed, test1);
		write_u32(bmiHeader.biClrImportant, test1);
	}
	if (bmiHeader.biSize >= 52)
	{
		write_u32(bmiHeader.biRedMask, test1);
		write_u32(bmiHeader.biGreenMask, test1);
		write_u32(bmiHeader.biBlueMask, test1);
	}

	if (bmiHeader.biSize >= 56)
	{
		write_u32(bmiHeader.biAlphaMask, test1);
	}
	if (bmiHeader.biSize >= 108)
	{
		write_u32(bmiHeader.biCSType, test1);
		fwrite(&bmiHeader.biEndpoints, 36, 1, test1);
		write_u32(bmiHeader.biGammaRed, test1);
		write_u32(bmiHeader.biGammaGreen, test1);
		write_u32(bmiHeader.biGammaBlue, test1);
	}
	if (bmiHeader.biSize >= 124)
	{
		write_u32(bmiHeader.biIntent, test1);
		write_u32(bmiHeader.biProfileData, test1);
		write_u32(bmiHeader.biProfileSize, test1);
		write_u32(bmiHeader.biReserved, test1);
	}


	//for (int i = 0; i < 1024; i++)
	//	putc(pal[i], test1);
	for (int i = 0; i < bmiHeader.biHeight; i++)
		for (int j = 0; j < bmiHeader.biWidth; j++)
		{
			if (i < 20)
			{
				putc(0, test1);
				putc(255, test1);
				putc(0, test1);
				putc(255, test1);
			}
			else
			{
				putc((pixels[i][j].rgbBlue + pixels[i][j].rgbGreen + pixels[i][j].rgbRed) / 3, test1);
				putc((pixels[i][j].rgbBlue + pixels[i][j].rgbGreen + pixels[i][j].rgbRed) / 3, test1);
				putc((pixels[i][j].rgbBlue + pixels[i][j].rgbGreen + pixels[i][j].rgbRed) / 3, test1);
				putc(255, test1);
			}
		}
	fclose(test1);

	system("pause");
	printf("Complete\n");
	return 0;
}


static unsigned short read_u16(FILE* fp)
{
	unsigned char b0, b1;

	b0 = getc(fp);
	b1 = getc(fp);

	return ((b1 << 8) | b0);
}


static unsigned int read_u32(FILE* fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


static int read_s32(FILE* fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

static void write_u16(unsigned short input, FILE* fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
}

static void write_u32(unsigned int input, FILE* fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}

static void write_s32(int input, FILE* fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}
unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
	if (mask == 0) {
		return 0;
	}

	// определение количества нулевых бит справа от маски
	int
		maskBufer = mask,
		maskPadding = 0;

	while (!(maskBufer & 1)) {
		maskBufer >>= 1;
		maskPadding++;
	}

	// применение маски и смещение
	return (byte & mask) >> maskPadding;
}
