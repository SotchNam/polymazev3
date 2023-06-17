#include "qtr.h"

void setup() {
	Serial.begin(9600);
	//qtr setup
	for (int i = 0; i < SensorCount; i++) {
		pinMode(irSensorPins[i], INPUT);
	}
}

void loop() {
	int i;
	irScan();
	Serial.print("sensorValues: ");
		for(i=0; i< SensorCount; i++){
			Serial.print(sensorValues[i]);
			Serial.print(", ");
		}
	Serial.println("");
	Serial.print("position: ");
	Serial.println(position);
	Serial.print("readsum: ");
	Serial.println(readsum);
	Serial.print("irFull: ");
	Serial.println(irFull);
	Serial.print("irRight: ");
	Serial.println(irRight);
	Serial.print("irLeft: ");
	Serial.println(irLeft);
	Serial.print("irNothing: ");
	Serial.println(irNothing);
	Serial.print("irMid: ");
	Serial.println(irMid);
}
