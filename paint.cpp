#include <iostream>
#include <fstream>
#include "bmplib.h"
#include "imgtools.h"


int main(int argc, char * argv[])
{
	if (argc != 2) { std::cout << "Use: \n\tinstagram filename \n"; return 0;}

	RGBimg img = {0, 0, nullptr};
	if (!readBMP(argv[1], img)) {
		std::cout << "Can not read BMP file '" << argv[1] << "'\n";
		return 1;
	}

	

	//обработка файла
	/*
	for (unsigned int row = 0; row < 80; ++row) {
		for (unsigned int col = 0; col < 80; ++col) {
			//std::cout << (int)img.pixels[row][col].blue << " ";
			RGB tmp = img.pixels[row][col];
			if (tmp.blue < 20 and tmp.green < 20 and tmp.red < 20) { std::cout << " ";}
			else if (tmp.blue < 40 and tmp.green < 40 and tmp.red < 40) { std::cout << "+"; }
			else if (tmp.blue < 60 and tmp.green < 60 and tmp.red < 60) { std::cout << "-"; }
			else if (tmp.blue < 80 and tmp.green < 80 and tmp.red < 80) { std::cout << "*"; }
			else if (tmp.blue < 100 and tmp.green < 100 and tmp.red < 100) { std::cout << "&"; }
			else if (tmp.blue < 120 and tmp.green < 120 and tmp.red < 120) { std::cout << "^"; }
			else if (tmp.blue < 140 and tmp.green < 140 and tmp.red < 140) { std::cout << "%"; }
			else if (tmp.blue < 160 and tmp.green < 160 and tmp.red < 160) { std::cout << "$"; }
			else if (tmp.blue < 180 and tmp.green < 180 and tmp.red < 180) { std::cout << "#"; }
			else if (tmp.blue < 200 and tmp.green < 200 and tmp.red < 200) { std::cout << "@"; }
			else if (tmp.blue < 220 and tmp.green < 220 and tmp.red < 220) { std::cout << "~"; }
			else if (tmp.blue < 240 and tmp.green < 240 and tmp.red < 240) { std::cout << ">"; }
			else { std::cout << (char)0xFE;}
		}
		std::cout << std::endl;
	}
	*/

	//toASCII(img, 200);

	logo(img);

	//сохранение файла

	if(!saveBMP(img, "output.bmp")) {
		std::cout << "Can not save to file 'output.bmp'\n";
	}
	freeMemory(img);
	return 0;
}
