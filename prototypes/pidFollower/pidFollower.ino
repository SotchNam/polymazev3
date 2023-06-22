#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

int motorspeed1 = 150;
int motorspeed2 = 150;

void setup() {
	//motor setup
	Serial.begin(9600);

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
	irScan();
	detectPostion();
	//if(!(irNothing || irFull)){
		pidControl();	
		forward(motorspeeda,motorspeedb);
	//}
	//else{
		//left(motorspeed1,motorspeed2);
		//buzzer();
	//}

	Serial.print("motor1:");
	Serial.print(motorspeeda);
	Serial.print("motor2:");
	Serial.print(motorspeedb);
	Serial.println(" ");
	Serial.print("position:");
	Serial.print(position);
	Serial.println(" ");
}
