#include <iostream>
using namespace std;

#include "BmpImage.h"

int main()
{	
	BmpImage *bildetest = new BmpImage;
	bildetest->lesBitmapFil("hoyde.bmp");
	//bildetest->invert();
	//bildetest->graaskala();
	bildetest->rodskala();
	/*
	Pixel ramme_pixel(0, 0, 0);
	bildetest->rammInnBilde(ramme_pixel, 40);
	
	Pixel antall_pixel(0, 0, 0);
	cout << bildetest->antallPiksler(antall_pixel) << endl;

	Pixel tegntilfeldig_pixel(255, 0, 0);
	bildetest->tegnTilfeldigePunkter(1200, tegntilfeldig_pixel);

	Pixel ny_pixel(255, 255, 255);
	bildetest->setPixel(1, 2, ny_pixel);

	bildetest->flip();
	bildetest->mirror();
	*/
	bildetest->lagreBitmapFil("hoyde1.bmp");

	delete bildetest;
	bildetest = 0;

	return 0;
}