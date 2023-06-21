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
	lightLed();
}
