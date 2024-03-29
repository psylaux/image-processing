#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Image.h"
#include <math.h>
#include <algorithm>

using namespace std;


void Multiply(Image &a, Image &b) {


	for (unsigned int i = 0; i < a.pixels.size(); i++) {

		a.pixels[i].blue = (int) (round(((double)a.pixels[i].blue*(double)b.pixels[i].blue)/255));
		a.pixels[i].green = (int)( round(((double)a.pixels[i].green*(double)b.pixels[i].green) / 255));
		a.pixels[i].red = (int) (round(((double)a.pixels[i].red*(double)b.pixels[i].red) / 255));
		
	

	}




}

void Subtract(Image &a, Image &b) {

	for (unsigned int i = 0; i < a.pixels.size(); i++) {
		
		int blue = (int)a.pixels[i].blue - (int) b.pixels[i].blue;
		int green = (int)(a.pixels[i].green - (int) b.pixels[i].green);
		int red = (int)(a.pixels[i].red - (int) b.pixels[i].red);

		if (blue > 255) { blue = 255; }
		if (green >255) { green = 255; }
		if (red > 255) { red = 255; }

		if (blue < 0) { blue = 0; }
		if (green < 0) { green = 0; }
		if (red< 0) { red = 0; }

		a.pixels[i].blue = blue;
		a.pixels[i].green = green;
		a.pixels[i].red = red;

	}

	
}

void Subtract2(Image &a, Image &b) {

	int red;
	int blue;
	int green;

	for (unsigned int i = 0; i < a.pixels.size(); i++) {

		blue = (int)(b.pixels[i].blue - a.pixels[i].blue);
		green = (int)(b.pixels[i].green - a.pixels[i].green);
		red = (int)(b.pixels[i].red - a.pixels[i].red);

		if (blue < 0) { blue = 0; }
		if (green < 0) { green = 0; }
		if (blue< 0) { red = 0; }

		a.pixels[i].blue = blue;
		a.pixels[i].green = green;
		a.pixels[i].red = red;

	}

}
void Screen(Image &a, Image &b) {


	for (unsigned int i = 0; i < a.pixels.size(); i++) {

		a.pixels[i].blue =(int) ( round(255 - (((double)(255 - a.pixels[i].blue))*((double)(255 - b.pixels[i].blue)) / 255)));
		a.pixels[i].green = (int) (round(255 - (((double)(255 - a.pixels[i].green))*((double)(255 - b.pixels[i].green)) / 255)));
		a.pixels[i].red = (int) (round(255 - (((double)(255 - a.pixels[i].red))*((double)(255 - b.pixels[i].red)) / 255)));
		
	}



}

void Overlay(Image &a, Image &b) {

	int red, green, blue;

	for (unsigned int i = 0; i < a.pixels.size(); i++) {

		Image::Pixel p;


		if (((a.pixels[i].red) / 255.0)>0.5) {
			p.red = (int) (((1 - (2 * (1 - a.pixels[i].red / 255.0)*(1 - b.pixels[i].red / 255.0)))*255.0) + 0.5f);
			red = p.red;
		}
		else {
			p.red = (int) (((2 * (a.pixels[i].red / 255.0)*(b.pixels[i].red / 255.0))*255.0) + 0.5f);
			red = p.red;
		}

		if (((a.pixels[i].green) / 255.0)>0.5) {
			p.green = (int) (((1 - (2 * (1 - a.pixels[i].green / 255.0)*(1 - b.pixels[i].green / 255.0)))*255.0) + 0.5f);
			green = p.green;
		}
		else {
			p.green = (int) (((2 * (a.pixels[i].green / 255.0)*(b.pixels[i].green / 255.0))*255.0) + 0.5f);
			green = p.green;
		}
		if (((a.pixels[i].blue) / 255.0)>0.5) {
			p.blue = (int) (((1 - (2 * (1 - a.pixels[i].blue / 255.0)*(1 - b.pixels[i].blue / 255.0)))*255.0) + 0.5f);
			blue = p.blue;
		}
		else {
			p.blue = (int) (((2 * (a.pixels[i].blue / 255.0)*(b.pixels[i].blue / 255.0))*255.0) + 0.5f);
			blue = p.blue;
		}

		a.pixels[i] = p;

	}


}



void Combine3(Image &red, Image &green, Image &blue) {

	for (unsigned int i = 0; i < red.pixels.size(); i++) {

		red.pixels[i].green = green.pixels[i].green;
		red.pixels[i].blue = blue.pixels[i].blue;
		
	}

}

void Rotate180(Image &a, Image &b) {
	
	int num = 0;
	for (unsigned int i = a.pixels.size() - 1; i > 0; i--) {

		b.pixels[i] = a.pixels[num];
		num++;
	}


}

void CollateHorizontal(Image &a, Image &b) {
	int totalWidth = a.headerObject.width + b.headerObject.width;
	int height = a.headerObject.height;
	int width = a.headerObject.width;
	bool activateleft = true;

	vector<Image::Pixel> pix;

	for (unsigned int i = 0; i < height; i++) {
		int current = 0;
		while (activateleft) {
			if (current == width) {
				activateleft = false;
				break;
			}
			pix.push_back(a.pixels[i*height+current]);
			current++;
		}
		current = 0;
		while (!activateleft) {
			if (current == width) {
				activateleft = true;
				break;
			}
			pix.push_back(b.pixels[i*height+current]);
			current++;
		}
	}

	a.SetSize(height, totalWidth);
	a.pixels = pix;
	
}

void CollateVertical(Image &a, Image &b) {
	int totalHeight = a.headerObject.height + b.headerObject.height;
	int height = a.headerObject.height;
	int width = a.headerObject.width;

	a.SetSize(totalHeight, width);

	vector<Image::Pixel> pix;
	
	for (unsigned int i = 0; i < b.pixels.size(); i++) {
		pix.push_back(b.pixels[i]);
	}

	for (unsigned int i = 0; i < a.pixels.size(); i++) {
		pix.push_back(a.pixels[i]);
	}

	a.pixels = pix;

}

int main()
{

	Image car = Image("files\\car");
	Image circles = Image("files\\circles");
	Image layer_blue = Image("files\\layer_blue");
	Image layer_green = Image("files\\layer_green");
	Image layer_red = Image("files\\layer_red");
	Image layer1 = Image("files\\layer1");
	Image layer2 = Image("files\\layer2");
	Image pattern1 = Image("files\\pattern1");
	Image pattern2 = Image("files\\pattern2");
	Image text = Image("files\\text");
	Image text2 = Image("files\\text2");

	Image part1 = Image("examples\\EXAMPLE_part1");
	Image part2 = Image("examples\\EXAMPLE_part2");
	Image part3 = Image("examples\\EXAMPLE_part3");
	Image part4 = Image("examples\\EXAMPLE_part4");
	Image part5 = Image("examples\\EXAMPLE_part5");
	Image part6 = Image("examples\\EXAMPLE_part6");
	Image part7 = Image("examples\\EXAMPLE_part7");
	Image part8_b = Image("examples\\EXAMPLE_part8_b");
	Image part8_g = Image("examples\\EXAMPLE_part8_g");
	Image part8_r = Image("examples\\EXAMPLE_part8_r");
	Image part9 = Image("examples\\EXAMPLE_part9");
	Image part10 = Image("examples\\EXAMPLE_part10");
	Image partec = Image("examples\\EXAMPLE_extraCredit");

	//layer1.WriteFile("layer1copy.tga");
/*
	cout << "Make a selection: ";
	cout << "\n1. Multiply layer1.tga with pattern1.tga";
	cout << "\n2. Subtract layer2.tga with car.tga";
	cout << "\n3. Multiply layer1.tga with pattern2.tga and add text";
	cout << "\n4. Multiply layer2.tga with circles.tga combined with option 3 using Screen";
	cout << "\n5. Combine layer1.tga with pattern1.tga using the Overlay blending mode";
	cout << "\n6. Load car.tga and add 200 to the green channel";
	cout << "\n7. Load car.tga and scale the red channel by 4 and blue by 0";
	cout << "\n8. Load car.tga and write each channel to a separate file";
	cout << "\n9. Combine layer_red.tga, layer_green.tga, layer_blue.tga";
	cout << "\n10. Rotate text2.tga 180 degrees\n";

	int option;
	cin >> option;

	cout << endl << endl << endl << "--------------------TESTING-----------------------" << endl;

	
	if (option > 0 && option < 11) {
		switch (option) {
			case 1:
			{
			*/


			
	cout << endl << endl << endl << "----TESTING----" << endl;

				Multiply(layer1, pattern1);
				layer1.WriteFile("part1.tga");

				cout << endl << "TEST 1 ";
				if (layer1.Equals(part1)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}

				layer1.ReloadImage();

/*			}break;
			case 2:
			{
	*/	
				Subtract2(layer2, car);
				layer2.WriteFile("part2.tga");

				cout << endl << "TEST 2 ";
					if (layer2.Equals(part2)) {

						cout << "SUCCEEDED";

					}
					else {
						cout << "FAILED";
					}

				layer2.ReloadImage();
		
	/*		}break;
			case 3:
			{
	*/
				Multiply(layer1, pattern2);
				//layer1.WriteFile("Part3_Multiply.tga");
				Screen(text, layer1);

				text.WriteFile("part3.tga");

				cout << endl << "TEST 3 ";
				if (text.Equals(part3)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				layer1.ReloadImage();
				text.ReloadImage();
	/*
			}break;
			case 4:
			{
		*/
				Multiply(layer2, circles);
				//circles.WriteFile("Part4_Multiply.tga");
				Subtract(layer2, pattern2);
			
				layer2.WriteFile("part4.tga");


				cout << endl << "TEST 4 ";
				if (layer2.Equals(part4)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}

				layer2.ReloadImage();

	/*		}break;
			case 5:
			{
		*/
				Overlay(pattern1, layer1);
				pattern1.WriteFile("part5.tga");


				cout << endl << "TEST 5 ";
				if (pattern1.Equals(part5)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}

				pattern1.ReloadImage();
	/*
			}break;
			case 6:
			{
		*/
				car.AddToChannel("green", 200);
				car.WriteFile("part6.tga");

				cout << endl << "TEST 6 ";
				if (car.Equals(part6)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				car.ReloadImage();
		
	/*		}break;
			case 7:
			{
		*/
				car.Scale("red", 4);
				car.Scale("blue", 0);

				car.WriteFile("part7.tga");

				cout << endl << "TEST 7 ";
				if (car.Equals(part7)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				car.ReloadImage();
	/*
			}break;
			case 8:
			{
		*/		car.ToChannel("blue");
				car.WriteFile("part8_b.tga");

				cout << endl << "TEST 8_B ";
				if (car.Equals(part8_b)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				car.ReloadImage();

				car.ToChannel("red");
				car.WriteFile("part8_r.tga");

				cout << endl << "TEST 8_R ";
				if (car.Equals(part8_r)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}

				car.ReloadImage();

				car.ToChannel("green");
				car.WriteFile("part8_g.tga");

				cout << endl << "TEST 8_G ";
				if (car.Equals(part8_g)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				car.ReloadImage();
	/*
			}break;
			case 9:
			{
		*/
				Combine3(layer_red, layer_green, layer_blue);
				layer_red.WriteFile("part9.tga");

				cout << endl << "TEST 9 ";
				if (layer_red.Equals(part9)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				layer_red.ReloadImage();
		
	/*		}break;
			case 10:
			{
		*/
				Image temp = text2;
				Rotate180(text2, temp);
				temp.WriteFile("part10.tga");

				cout << endl << "TEST 10 ";
				if (temp.Equals(part10)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}


				text2.ReloadImage();
/*
			}break;
		}
	}
	else {
		cout << "Invalid option";
	}
	*/

	//EC

				CollateHorizontal(car, circles);
				CollateHorizontal(text, pattern1);

				CollateVertical(car, text);

				car.WriteFile("extracredit.tga");

				cout << endl << "TEST EXTRA CREDIT ";
				if (car.Equals(partec)) {

					cout << "SUCCEEDED";

				}
				else {
					cout << "FAILED";
				}

				text.ReloadImage();
				car.ReloadImage();

	//EC

				cout << endl;


		
	

	return 0;
}

