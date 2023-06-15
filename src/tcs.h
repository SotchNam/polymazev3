//based on the colorview example by adafruit
#include <Wire.h>
#include "Adafruit_TCS34725.h"

//for rgb led
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
//needs change
#define redpin 3
#define greenpin 5
#define bluepin 6

Adafruit_TCS34725 tcs = Adafruit_TCS34725();
//for sensor input
float red, green, blue;


//for outputs
enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN
};
Color color;

//something to do with converting to something we see better idk
//on another thought isnt this used for live visuals?
byte gammatable[256];
void gammaSetup(){
	for (int i=0; i<256; i++) {
		float x = i;
		x /= 255;
		x = pow(x, 2.5);
		x *= 255;
		gammatable[i] = x;
	}
}

//to be in setup code
void ledSetup(){
	ledcAttachPin(redpin, 1);
	ledcSetup(1, 12000, 8);
	ledcAttachPin(greenpin, 2);
	ledcSetup(2, 12000, 8);
	ledcAttachPin(bluepin, 3);
	ledcSetup(3, 12000, 8);
}

//detects the colors
void detectColor(){
	tcs.setInterrupt(false);  // turn on LED
	delay(60);  // takes 50ms to read
	tcs.getRGB(&red, &green, &blue);
	tcs.setInterrupt(true);  // turn off LED
	/*
	//gibirish values pls fix //needs change
	if (red > 12 && red < 30   &&  grn > 40 && grn < 70    &&  blu > 33 && blu < 70)   color = "RED";
	else if (red > 50 && red < 95   &&  grn > 35 && grn < 70    &&  blu > 45 && blu < 85)   color = "GREEN";
	else if (red > 10 && red < 20   &&  grn > 10 && grn < 25    &&  blu > 20 && blu < 38)   color = "YELLOW";
	else if (red > 65 && red < 125  &&  grn > 65 && grn < 115   &&  blu > 32 && blu < 65)   color = "BLUE";
	else  color = "NO_COLOR";
	*/
}

//output detected color to the rgb led, values should be ok
void lightLed(){
	switch (color){
		case RED:
			red = 255;
			green = 0;
			blue = 0;
		break;
		case GREEN:
			red = 0;
			green = 255;
			blue = 0;
		break;
		case BLUE:
			red = 0;
			green = 0;
			blue = 255;
		break;
		case CYAN:
			red = 0;
			green = 255;
			blue = 255;
		break;
		case YELLOW:
			red = 255;
			green = 255;
			blue = 0;
		break;
		case MAGENTA:
			red = 255;
			green = 0;
			blue = 255;
		break;
		default:
			red = 0;
			green = 0;
			blue = 0;
		break;
	}
	//ngl still not sure bout the gammatable but adafruit say it gud so
	ledcWrite(1, gammatable[(int)red]);
	ledcWrite(2, gammatable[(int)green]);
	ledcWrite(3, gammatable[(int)blue]);
}
