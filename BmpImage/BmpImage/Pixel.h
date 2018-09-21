#pragma once
class Pixel {
public:
	//Konstruktør med flere argumenter:
	Pixel(int _r, int _g, int _b);
	//Funksjon for å endre fargene til en piksel:
	void edit(int _r, int _g, int _b);
	//Funksjoner for å lese ut R,G og B verdiene:
	int getR();
	int getG();
	int getB();
	void changeComponent(int component, unsigned char newValue);
	int getComponent(int component);
private:
	//Medlemsvariabler:
	int r;
	int g;
	int b;
};