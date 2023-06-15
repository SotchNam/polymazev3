#include "motors.h"
#include "qtr.h"
#include "tcs.h"

/*other pins*/
//needs change
#define buzzerPin 99

/*functions declaration*/
void buzzer();

/*start main*/
void setup() {
	//motor setup
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(motor1Speed, OUTPUT);
	pinMode(motor2Speed, OUTPUT);
	//qtr setup
	for (int i = 0; i < SensorCount; i++) {
		pinMode(irSensorPins[i], INPUT);
	}
	//tcs setup
	gammaSetup();
	ledSetup();
	//buzzer setup
	pinMode(buzzerPin, OUTPUT);
	buzzer();
}

void loop() {
	//to be filled with logic
}

/*functions*/
void buzzer(){
	tone(buzzerPin, 1000);
	delay(100);
	noTone(buzzerPin);
}
