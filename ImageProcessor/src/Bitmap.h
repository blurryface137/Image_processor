#ifndef BITMAP_H_
#define BITMAP_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>

typedef int LONG;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct tagBITMAPFILEHEADER {
    WORD    bfType; // 2  /* Magic identifier */
    DWORD   bfSize; // 4  /* File size in bytes */
    WORD    bfReserved1; // 2
    WORD    bfReserved2; // 2
    DWORD   bfOffBits; // 4 /* Offset to image data, bytes */
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD    biSize; // 4 /* Header size in bytes */
    LONG     biWidth; // 4 /* Width of image */
    LONG     biHeight; // 4 /* Height of image */
    WORD     biPlanes; // 2 /* Number of color planes */
    WORD     biBitCount; // 2 /* Bits per pixel */
    DWORD    biCompress; // 4 /* Compression type */
    DWORD    biSizeImage; // 4 /* Image size in bytes */
    LONG     biXPelsPerMeter; // 4
    LONG     biYPelsPerMeter; // 4 /* Pixels per meter */
    DWORD    biClrUsed; // 4 /* Number of colors */
    DWORD    biClrImportant; // 4 /* Important colors */
} __attribute__((packed)) BITMAPINFOHEADER;

typedef struct {
	BYTE    B;
	BYTE    G;
	BYTE    R;
} RGB;

class Bitmap final {
public:
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
	RGB *data;

	Bitmap();
	~Bitmap();

	int read(const char *file_name);
	int write(const char *file_name);
};

#endif /* BITMAP_H_ */
