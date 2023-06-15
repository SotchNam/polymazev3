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
	//pin declaration
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(motor1Speed, OUTPUT);
	pinMode(motor2Speed, OUTPUT);
	for (int i = 0; i < SensorCount; i++) {
		pinMode(irSensorPins[i], INPUT);
	}
	pinMode(buzzerPin, OUTPUT);
}

void loop() {

}

/*functions*/

void buzzer(){
	tone(buzzerPin, 1000);
	delay(100);
	noTone(buzzerPin);
}
