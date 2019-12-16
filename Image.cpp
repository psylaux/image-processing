#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Image.h"

using namespace std;


Image::Image() {}

Image::Image(string a) {

	GetFileInfo(a + ".tga");

}


void Image::GetFileInfo(string filename) {
	
	filepath = filename;

	ifstream file(filepath, ios_base::binary);

	if (file.is_open()) {
		
	
			file.read(&headerObject.idLength, sizeof(headerObject.idLength));
			file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
			file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
			file.read((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
			file.read((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
			file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
			file.read((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
			file.read((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
			file.read((char *)&headerObject.width, sizeof(headerObject.width));
			file.read((char *)&headerObject.height, sizeof(headerObject.height));
			file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
			file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
		


		//pixel data
		unsigned int heightwidth = headerObject.width*headerObject.height;

		vector<Pixel> v(heightwidth);

		for (unsigned int i = 0; i < heightwidth; i++) {

			//Pixel p;

			file.read((char *)&v[i].blue, 1);
			file.read((char *)&v[i].green, 1);
			file.read((char *)&v[i].red, 1);

		}

		pixels = v;

		cout << "...";

	}

}

void Image::SetSize(int height, int width) {
	this->headerObject.height = height;
	this->headerObject.width = width;
}

void Image::PrintFileInfo(Header file) {

	cout << "HEADER INFO\n";
	cout << "------------\n\n";

	cout << "ID Length: " << (int) file.idLength;
	cout << "\nColor Map Type: " << (int) file.colorMapType;
	cout << "\nData Type Code: " << (int) file.dataTypeCode;
	cout << "\nColor Map Origin: " << (int) file.colorMapOrigin;
	cout << "\nColor Map Length: " << (int) file.colorMapLength;
	cout << "\nColor Map Depth: " << (int) file.colorMapDepth;
	cout << "\nxOrigin: " << (int) file.xOrigin;
	cout << "\nyOrigin: " << (int) file.yOrigin;
	cout << "\nWidth: " << (int) file.width;
	cout << "\nHeight: " << (int) file.height;
	cout << "\nBits Per Pixel: " << (int) file.bitsPerPixel;
	cout << "\nImage Descriptor: " << (int) file.imageDescriptor;
 
}


void Image::CopyPixelInfo(string a) {


	ofstream outfile(a, ios_base::binary);

	if (outfile.is_open()) {

		for (unsigned int i = 0; i < pixels.size();i++) {

			outfile.write((char *)&pixels[i].blue, 1); 
			outfile.write((char *)&pixels[i].green, 1); 
			outfile.write((char *)&pixels[i].red, 1);
			
		}

	}

}



void Image::WriteFile(string a) {

	string fileName = "output/";
	fileName += a;

	ofstream outfile(fileName, ios_base::binary);

	if (outfile.is_open()) {
		outfile.write((char *)&headerObject.idLength, sizeof(headerObject.idLength));
		outfile.write((char *)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
		outfile.write((char *)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
		outfile.write((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
		outfile.write((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
		outfile.write((char *)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
		outfile.write((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
		outfile.write((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
		outfile.write((char *)&headerObject.width, sizeof(headerObject.width));
		outfile.write((char *)&headerObject.height, sizeof(headerObject.height));
		outfile.write((char *)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
		outfile.write((char *)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
	
		for (unsigned int i = 0; i < pixels.size(); i++) {

			outfile.write((char *)&pixels[i].blue, 1);
			outfile.write((char *)&pixels[i].green, 1);
			outfile.write((char *)&pixels[i].red, 1);

		}

	
	}

	outfile.close();

}

void Image::ReloadImage() {


	ifstream file(filepath, ios_base::binary);

	if (file.is_open()) {

		if (file.is_open()) {
			file.read(&headerObject.idLength, sizeof(headerObject.idLength));
			file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
			file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
			file.read((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
			file.read((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
			file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
			file.read((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
			file.read((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
			file.read((char *)&headerObject.width, sizeof(headerObject.width));
			file.read((char *)&headerObject.height, sizeof(headerObject.height));
			file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
			file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
		}


		//pixel data
		unsigned int heightwidth = headerObject.width*headerObject.height;

		for (unsigned int i = 0; i < heightwidth; i++) {

			Pixel p;

			file.read((char *)&p.blue, 1);
			file.read((char *)&p.green, 1);
			file.read((char *)&p.red, 1);


			pixels[i].blue = p.blue;
			pixels[i].green = p.green;
			pixels[i].red = p.red;

		}


	}

}

void Image::AddToChannel( string channel, int value ) {

	if (channel == "blue") {
		
		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].blue + value) > 255) {
				pixels[i].blue = 255; 
			}
			else {
				pixels[i].blue += value; 
			}

		}

	}
	if (channel == "green") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].green + value) > 255) {
				pixels[i].green = 255;
			}
			else {
				pixels[i].green += value;
			}

		}
	}
	if (channel == "red") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].red + value) > 255) {
				pixels[i].red = 255;
			}
			else {
				pixels[i].red += value;
			}

		}
	}



}

void Image::Scale(string channel, int value) {

	if (channel == "blue") {

		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].blue * value) > 255) {
				pixels[i].blue = 255;
			}
			else {
				pixels[i].blue *= value;
			}

		}

	}
	if (channel == "green") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].green * value) > 255) {
				pixels[i].green = 255;
			}
			else {
				pixels[i].green *= value;
			}

		}
	}
	if (channel == "red") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			if ((pixels[i].red * value) > 255) {
				pixels[i].red = 255;
			}
			else {
				pixels[i].red *= value;
			}

		}
	}





}


void Image::ToChannel(string channel) {

	int value = 0;

	if (channel == "blue") {

		for (unsigned int i = 0; i < pixels.size(); i++) {

			value = pixels[i].blue;
			pixels[i].green = value;
			pixels[i].red = value;

		}

	}
	else if (channel == "green") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			value = pixels[i].green;
			pixels[i].blue = value;
			pixels[i].red = value;

		}

	}
	else if (channel == "red") {


		for (unsigned int i = 0; i < pixels.size(); i++) {

			value = pixels[i].red;
			pixels[i].green = value;
			pixels[i].blue = value;

		}

	}

}


bool Image::Equals(Image image) {

	bool equal = true;

	if (headerObject.idLength != image.headerObject.idLength) {
		equal = false;
		cout << "Id length not equal";
	}
	if (headerObject.colorMapType != image.headerObject.colorMapType) {
		equal = false;
		cout << "Color Map Type not equal";
	}
	if (headerObject.dataTypeCode != image.headerObject.dataTypeCode) {
		equal = false;
		cout << "Data Type code not equal";
	}
	if (headerObject.colorMapOrigin != image.headerObject.colorMapOrigin) {
		equal = false;
		cout << "Color Map Origin not equal";
	}
	if (headerObject.colorMapLength != image.headerObject.colorMapLength) {
		equal = false;
		cout << "Color Map Length not equal";
	}
	if (headerObject.colorMapDepth != image.headerObject.colorMapDepth) {
		equal = false;
		cout << "Color Map Depth not equal";
	}
	if (headerObject.xOrigin != image.headerObject.xOrigin) {
		equal = false;
		cout << "X Origin not equal";
	}
	if (headerObject.yOrigin != image.headerObject.yOrigin) {
		equal = false;
		cout << "Y Origin not equal";
	}
	if (headerObject.width != image.headerObject.width) {
		equal = false;
		cout << "Width not equal";
	}
	if (headerObject.height != image.headerObject.height) {
		equal = false;
		cout << "Height not equal";
	}
	if (headerObject.bitsPerPixel != image.headerObject.bitsPerPixel) {
		equal = false;
		cout << "Bits per pixel not equal";
	}
	if (headerObject.imageDescriptor != image.headerObject.imageDescriptor) {
		equal = false;
		cout << "Image Descriptor not equal";
	}

	if (pixels.size() != image.pixels.size()) {
		equal = false;
		cout << "pixels not the same";
	}

	for (unsigned int i = 0; i < pixels.size(); i++) {

		if (pixels[i].blue != image.pixels[i].blue) {
			equal = false;
			cout << "Blue pixel incorrect at pixel " << i;
		}
		if (pixels[i].green != image.pixels[i].green) {
			equal = false;
			cout << "Green pixel incorrect at pixel " << i;
		}
		if (pixels[i].red != image.pixels[i].red) {
			equal = false;
			cout << "Red pixel incorrect at pixel " << i;
		}

	}

	return equal;

}