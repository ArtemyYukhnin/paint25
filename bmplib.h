#include <cstdint>

#pragma once

typedef unsigned char BYTE;
typedef std::uint16_t WORD;
typedef std::uint32_t DWORD;
typedef std::int32_t LONG;


#pragma pack(push,1)
struct BITMAPINFOHEADER {
	DWORD biSize;			// размер структуры в байтах
	LONG  biWidth;			// ширина в пикселях
	LONG  biHeight;			// высота в пикселях
	WORD  biPlanes;			// всегда 1
	WORD  biBitCount;		// количество бит на цвет 0 | 1 | 2 | 4 | 8 | 16 | 24 | 32 | 48 | 64
	DWORD biCompression;	// есть или нет сжатия
	DWORD biSizeImage;		// размер изображенеия
	LONG  biXPelsPerMeter;	//горизонтальное разрешение
	LONG  biYPelsPerMeter;	//вертикальное разрешение
	DWORD biClrUsed;		// количество цветов (в том случае, если используется таблица цветов)
	DWORD biClrImportant;	// количество существенных цветов
};

struct BITMAPFILEHEADER {
	WORD  bfType; // тип файла
	DWORD bfSize; // размер файла
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits; // смещение до поля данных
};
#pragma pack(pop)

struct RGB {
	BYTE red;
	BYTE green;
	BYTE blue;
};

struct RGBimg {
	unsigned int widht;
	unsigned int height;
	RGB** pixels;
};

void print(const BITMAPFILEHEADER& bmfh);
void print(const BITMAPINFOHEADER& x);
RGBimg createImg(unsigned int widht, unsigned int height);
void freeMemory(RGBimg& img);
bool readBMP(const char* fname, RGBimg& img);
bool saveBMP(const RGBimg& img, const char* filename);
