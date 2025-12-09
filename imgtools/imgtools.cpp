#include "imgtools.h"
#include <iostream>

void logo(RGBimg& img) {
	if (img.widht > 25 and img.height > 25) {
		//add logo
		RGB brush = { 250, 52, 52 };

		for (unsigned int row = 0; row < 69; ++row) {
			img.pixels[row][0] = brush;
			img.pixels[row][68] = brush;
		}
		for (unsigned int col = 0; col < 69; ++col) {
			img.pixels[0][col] = brush;
			img.pixels[68][col] = brush;
		}
		for (unsigned int i = 0; i < 69; ++i) {
			img.pixels[i][i] = brush;
			img.pixels[i][68 - i] = brush;
		}

	}

}


void toASCII(RGBimg& img,BYTE level) {
	for (unsigned int row = 0; row < 80; ++row) {
		for (unsigned int col = 0; col < 80; ++col) {
			//std::cout << (int)img.pixels[row][col].blue << " ";
			RGB tmp = img.pixels[row][col];
			if (tmp.red < level) { std::cout << " "; }
			//if (tmp.blue < 20 and tmp.green < 20 and tmp.red < 20) { std::cout << " "; }
			//else if (tmp.blue < 40 and tmp.green < 40 and tmp.red < 40) { std::cout << "+"; }
			//else if (tmp.blue < 60 and tmp.green < 60 and tmp.red < 60) { std::cout << "-"; }
			//else if (tmp.blue < 80 and tmp.green < 80 and tmp.red < 80) { std::cout << "*"; }
			//else if (tmp.blue < 100 and tmp.green < 100 and tmp.red < 100) { std::cout << "&"; }
			//else if (tmp.blue < 120 and tmp.green < 120 and tmp.red < 120) { std::cout << "^"; }
			//else if (tmp.blue < 140 and tmp.green < 140 and tmp.red < 140) { std::cout << "%"; }
			//else if (tmp.blue < 160 and tmp.green < 160 and tmp.red < 160) { std::cout << "$"; }
			//else if (tmp.blue < 180 and tmp.green < 180 and tmp.red < 180) { std::cout << "#"; }
			//else if (tmp.blue < 200 and tmp.green < 200 and tmp.red < 200) { std::cout << "@"; }
			//else if (tmp.blue < 220 and tmp.green < 220 and tmp.red < 220) { std::cout << "~"; }
			//else if (tmp.blue < 240 and tmp.green < 240 and tmp.red < 240) { std::cout << ">"; }
			else { std::cout << (char)0x95; }
		}
		std::cout << std::endl;
	}
}
