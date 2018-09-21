#pragma once

#include <vector>
using namespace std;

#include "Pixel.h"

class BmpImage
{
public:
	BmpImage();
	~BmpImage();
	bool lesBitmapFil(string filename);
	bool lagreBitmapFil(string filename);
	bool setPixel(int x, int y, Pixel &ny_pixel);
	void graaskala();
	void invert();

	int getwidth();
	int getheigth();
	int getheadersize();
	int getoffset();
	int getstuffing();

	void rammInnBilde(Pixel &Farge, int rammeBredde);
	int antallPiksler(Pixel &Farge);
	void tegnTilfeldigePunkter(int antall, Pixel &Farge);
	void flip();
	void mirror();

private:
	vector<vector<Pixel>> pixelData;
	unsigned int width = 0;
	unsigned int heigth = 0;

	int HEADERSIZE;
	unsigned char *header;
	unsigned char enPixel[3];
	unsigned int offset = -1;
	int stuffing;
};
