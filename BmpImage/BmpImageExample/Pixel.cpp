#include "Pixel.h"
//Konstruktør:
Pixel::Pixel(int _r, int _g, int _b) {
	r = _r; g = _g; b = _b;
};
//Funksjon for å endre fargene til en piksel:
void Pixel::edit(int _r, int _g, int _b) {
	r = _r;
	g = _g;
	b = _b;
};
//Funksjoner for å lese ut R,G og B verdiene:
int Pixel::getR() {
	return r;
};
int Pixel::getG() {
	return g;
};
int Pixel::getB() {
	return b;
};
//Funksjon som endrer verdien til en av fargekomponentene:
void Pixel::changeComponent(int component, unsigned char newValue) {
	switch (component) {
	case 0:
		r = newValue;
		break;
	case 1:
		g = newValue;
		break;
	case 2:
		b = newValue;
		break;
	}
};
//Returnerer en av fargekomponentene:
int Pixel::getComponent(int component) {
	switch (component) {
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	}
};