#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

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
	//indicate the beginning of the end
	buzzer();
}

void loop() {
	//to be filled with logic
}
