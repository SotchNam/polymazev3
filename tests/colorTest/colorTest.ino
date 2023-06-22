#include "tcs.h"

void setup() {
	Serial.begin(9600); 
	ledSetup();
	gammaSetup();

	if (tcs.begin()) {
	    Serial.println("Found sensor");
	  } else {
	    Serial.println("No TCS34725 found ... check your connections");
	  }

}

float clear;

void loop() {
	delay(500);
	detectColor();
	Serial.print("rgb: "); // print a message
	Serial.print(red); 
	Serial.print(", ");
	Serial.print(green); 
	Serial.print(", ");
	Serial.print(blue); 
	Serial.println(" ");
	Serial.print(color);
	Serial.println(" ");

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

	Serial.print("rgbr: "); // print a message
	Serial.print(r); 
	Serial.print(", ");
	Serial.print(g); 
	Serial.print(", ");
	Serial.print(b); 
	Serial.print(",");
	Serial.print(c);
	Serial.println(" ");



	for (int i=0;i<6;i++){
		Serial.print(red > lower_bounds[i][0] && red < upper_bounds[i][0]);
		Serial.print(green > lower_bounds[i][1] && green < upper_bounds[i][1]);
		Serial.print(blue > lower_bounds[i][2] && blue < upper_bounds[i][2]);
		Serial.println(" ");
	}
		lightLed();
	delay(1000);

	/*
	for( int i=0; i<6;i++){
		color= Colors(i);	
		lightLed();
	Serial.print(color);
	Serial.println(" ");
		delay(1000);
	}
		*/
}
