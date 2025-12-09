#include "bmplib.h"
#include <iostream>
#include <fstream>


void print(const BITMAPFILEHEADER& bmfh) {
	std::cout << bmfh.bfType << std::endl;
	std::cout << bmfh.bfSize << std::endl;
	std::cout << bmfh.bfOffBits << std::endl;
}

void print(const BITMAPINFOHEADER& x) {
	std::cout << "biSize = " << x.biSize << std::endl;
	std::cout << "biWidth = " << x.biWidth << std::endl;
	std::cout << "biHeight = " << x.biHeight << std::endl;
	std::cout << "biPlanes = " << x.biPlanes << std::endl;
	std::cout << "biBitCount = " << x.biBitCount << std::endl;
	std::cout << "biCompression = " << x.biCompression << std::endl;
	std::cout << "biSizeImage = " << x.biSizeImage << std::endl;
	std::cout << "biXPelsPerMeter = " << x.biXPelsPerMeter << std::endl;
	std::cout << "biYPelsPerMeter = " << x.biYPelsPerMeter << std::endl;
	std::cout << "biClrUsed = " << x.biClrUsed << std::endl;
	std::cout << "biClrImportant = " << x.biClrImportant << std::endl;
}

RGBimg createImg(unsigned int widht, unsigned int height) {
	RGBimg img;
	img.widht = widht;
	img.height = height;
	img.pixels = new RGB * [height];
	for (unsigned int row = 0; row < height; ++row) {
		img.pixels[row] = new RGB[widht];
	}
	return img;
}


void freeMemory(RGBimg& img) {
	for (unsigned int row = 0; row < img.height; ++row) {
		delete[] img.pixels[row];
	}
	delete[] img.pixels;
	img.pixels = nullptr;
	img.widht = 0;
	img.height = 0;
}

bool readBMP(const char* fname, RGBimg& img) {
	std::ifstream inFile(fname, std::ios_base::binary);
	if (!inFile) { return false; }
	BITMAPFILEHEADER bmfh;
	inFile.read((char*)&bmfh, sizeof(bmfh));
	print(bmfh);
	if (bmfh.bfType != int('M') * 256 + int('B')) { //19778
		inFile.close();
		return false;
	}

	BITMAPINFOHEADER bmih;
	inFile.read((char*)&bmih, sizeof(bmih));
	print(bmih);

	if (bmih.biCompression != 0) {
		inFile.close();
		return false;
	}
	freeMemory(img);
	img = createImg(bmih.biWidth, bmih.biHeight);

	if (bmih.biBitCount == 24) {
		RGB tmp;
		BYTE offset_array[16] = { 0 };
		const int offset = (img.widht % 4) ? (4 - (3 * img.widht) % 4) : 0;
		for (unsigned int row = img.height; row > 0; --row) {
			for (unsigned int col = 0; col < img.widht; ++col) {
				inFile.read((char*)&tmp, sizeof(tmp));
				std::swap(tmp.blue, tmp.red);
				img.pixels[row - 1][col] = tmp;
			}
			inFile.read((char*)offset_array, offset);
		}
	}
	else {
		inFile.close();
		return false;
	}

	inFile.close();
	return true;
}

bool saveBMP(const RGBimg& img, const char* filename) {
	std::ofstream outBMP(filename, std::ios_base::binary);
	if (!outBMP) {
		return false;
	}
	BITMAPFILEHEADER bmfh;
	char bfType[] = { 'B', 'M' };
	bmfh.bfType = *((WORD*)bfType);
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + img.height * img.widht * 3;
	outBMP.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));


	BITMAPINFOHEADER bmih;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = img.widht;
	bmih.biHeight = img.height;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = 0;
	bmih.biSizeImage = bmfh.bfSize - bmfh.bfOffBits;
	bmih.biXPelsPerMeter = 1;
	bmih.biYPelsPerMeter = 1;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;
	outBMP.write((char*)&bmih, sizeof(BITMAPINFOHEADER));

	const int offset = (img.widht % 4) ? (4 - (3 * img.widht) % 4) : 0;
	BYTE offset_array[4] = { 0 };

	for (unsigned int row = img.height; row > 0; --row) {
		for (unsigned int col = 0; col < img.widht; ++col) {
			RGB tmp = img.pixels[row - 1][col];
			std::swap(tmp.blue, tmp.red);
			outBMP.write((char*)&tmp, sizeof(tmp));
		}
		outBMP.write((char*)offset_array, offset);
	}
	outBMP.close();
	return true;
}
