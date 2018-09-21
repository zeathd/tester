#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

#include "Pixel.h"

void graaSkala(vector<vector<Pixel>> &pixelData, int _width, int _height);
void invert(vector<vector<Pixel>> &pixelData, int _width, int _height);

int main()
{
	fstream infile;
	string innfilnavn = "flaaklypa.bmp";
	string utfilnavn = "flaaklypa_grayscale.bmp";
	unsigned int offset; //Angir starten på pikslene
	unsigned int width; //Bildets bredde i antall piksler
	unsigned int height; //Bildets høyde i antall piksler
	const int HEADERSIZE = 54; //Fast verdi for 24 bits DIB.
	unsigned char header[HEADERSIZE]; //Kan holde på hele headeren
	unsigned char enPixel[3]; //Bestående av 3 byte

							  //En vektor/tabell som vil inneholde alle pikslene i fila.
							  //Vektoren består av vektorer, der hver vektor representerer
							  //en pikselrad.
	vector<vector<Pixel>> pixelData;
	//<
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	// <p p p p p p p p p p p p p p>
	//>

	//Åpner bitmapfila m.m.
	infile.open(innfilnavn.c_str(), ios::binary | ios::in);
	if (infile.fail()) {
		cout << "Feil ved åpning av fil" << endl;
	}
	else {
		//Leser hele headeren slik at den kan brukes i ny fil:
		infile.read((char *)header, HEADERSIZE);
		//Søker frem til 10. byte (fra start):
		infile.seekg(10, ios::beg);
		infile.read((char*)&offset, 4);

		infile.seekg(18, ios::beg); //flytter lesefilpekeren til posisjon 18
		infile.read((char*)&width, 4); //i antall piksler
		infile.read((char*)&height, 4); //i antall piksler

		//Plasserer filpeker til starten av pikseldata:
		infile.seekg(offset);

		//NB!Bredden (i antall piksler) på bildet skal være delelig på 4.
		//Dersom bredden på bildet er delelig på 4 vil stuffing være lik 0,
		//ellers vil den bli 1,2 eller 3.
		int stuffing = width % 4;
		//pix holder rede på antall leste piksler per linje
		int pix = 0;
		//Leser alle pikslene (3 byte per piksel) fra fila, rad for rad:
		for (unsigned int i = 0; i < height; i++)
		{
			//Oppretter en ny tom rad‐vektor:
			vector<Pixel> rad;
			//Leser width antall piksler:
			for (unsigned int j = 0; j < width; j++)
			{
				//Leser tre bytes (en piksel) i slengen, leses inn i enPixel:
				infile.read((char *)enPixel, 3);
				//Øker antall piksler for denne linja med 1:
				pix++;
				//Oppretter piksel‐objekt og legger til radvektor:
				Pixel nyPixel((int)enPixel[2], (int)enPixel[1], (int)enPixel[0]);
				rad.push_back(nyPixel);
			}
			//Når antall piksler er lik bredden sjekker vi for evt. stuffing:
			//p settes lik filpekeren
			int p = infile.tellp();
			//Søker forbi evt. stuffbytes:
			infile.seekg(p + stuffing);
			pix = 0;
			//Lagrer raden:
			pixelData.push_back(rad);

		}

		//graaSkala(pixelData, width, height);
		graaSkala(pixelData, width, height);

		//Skriver manipulert innhold til ny fil:
		fstream outfile;
		outfile.open(utfilnavn.c_str(), ios::binary | ios::out);

		//Skriver headeren:
		outfile.write((char *)header, HEADERSIZE);
		//"Hjelpebytes":
		unsigned char utdata[3];
		unsigned char stuffBytes[3] = { 0, 0, 0 };
		//Plasserer skrivepeker (byte 54):
		outfile.seekp(offset, ios::beg);
		//pix holder rede på antall skrevne piksler per linje
		pix = 0;
		//Skriver alle pikslene fra pixelData til den nye fila:
		for (int i = 0; i < height; i++) {
			//Henter rad nr i (0 = første pikselrad):
			vector<Pixel> rad = pixelData[i];
			//Leser piksel for piksel fra rad nr i:
			for (int j = 0; j < width; j++) {
				Pixel *p = &(rad.at(j));
				utdata[0] = p->getB();
				utdata[1] = p->getG();
				utdata[2] = p->getR();
				outfile.write((char *)utdata, 3);
				pix++;
			}
			//Legger til evt. stuffing:
			outfile.write((char *)stuffBytes, stuffing);
			pix = 0;
		}
		infile.close();
		outfile.close();

	}

	


	return 0;
}

void graaSkala(vector<vector<Pixel>> &pixelData, int _width, int _height) {
	int grey = 0;
	//Gjennomløper alle rader:
	for (int i = 0; i < _height; i++) {
		//Henter rad nr i (rad 0 er nederste pikselrad i bildet):
		vector<Pixel> *rad = &(pixelData[i]);
		//Gjennomløper alle pikslene i rad nr i:
		for (int j = 0; j < _width; j++) {
			Pixel *p = &(rad->at(j));//Henter referanse til piksel.
									 //Gråfarge basert på snitt av rgb‐fargen:
			grey = (p->getR() + p->getG() + p->getB()) / 3;
			//Setter grå pikselfarge:
			p->edit(grey, grey, grey); //Endrer piksel.       
		}
	}
}

void invert(vector<vector<Pixel>> &pixelData, int _width, int _height) {
	int red = 0, green = 0, blue = 0;
	//Gjennomløper alle rader:
	for (int i = 0; i < _height; i++) {
		//Henter rad nr i (rad 0 er nederste pikselrad i bildet):
		vector<Pixel> *rad = &(pixelData[i]);
		//Gjennomløper alle pikslene i rad nr i:
		for (int j = 0; j < _width; j++) {
			Pixel *p = &(rad->at(j));//Henter referanse til piksel.
									 //Gråfarge basert på snitt av rgb‐fargen:
			red = (255 - p->getR());
			green = (255 - p->getG());
			blue = (255 - p->getB());
			//Setter grå pikselfarge:
			p->edit(red, green, blue); //Endrer piksel.       
		}
	}
}