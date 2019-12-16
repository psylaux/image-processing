#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


struct Image {

	struct Header {

		char  idLength;
		char  colorMapType;
		char  dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char  colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char  bitsPerPixel;
		char  imageDescriptor;

	};

	struct Pixel {

		unsigned char red;
		unsigned char green;
		unsigned char blue;

	};

	Header headerObject;
	vector<Pixel> pixels;
	string filepath;
	
	Image();
	Image(string);

	void GetFileInfo(string);
	void PrintFileInfo(Header);
	void CopyPixelInfo(string);
	void WriteFile(string);
	void AddToChannel(string, int);
	void Scale(string, int);
	void ToChannel(string);
	void ReloadImage();
	bool Equals(Image);
	void SetSize(int, int);

};
