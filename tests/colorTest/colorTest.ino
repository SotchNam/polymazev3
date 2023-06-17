#include "tcs.h"

void setup() {
	ledSetup();
}

void loop() {
	delay(500);
	detectColor();
	lightLed();
}
