#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

const int turningSpeed= 130; //speed that it turns with
const int turningTime= 1100; //time to turn
const int turningTime2= 200;

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
	forward(turningSpeed,turningSpeed);
}

void loop() {
	irScan();
	detectPostion();

	if (!irNothing){//checks for line existance
		if(irMid){//no intersections
			pidControl();
			forward(motorspeeda,motorspeedb);
		}

		//follow right wall 
		else { //intersection or turn
			if(irRight || irFull) {
				//buzzer();
				right(turningSpeed, turningSpeed);
				delay(50);
				//delay(turningTime);
				//forward(turningSpeed,turningSpeed);
				//delay(turningTime2);
			}
			else{
				//buzzer();
				left(turningSpeed, turningSpeed);
				delay(50);
				//delay(turningTime);
				//forward(turningSpeed,turningSpeed);
				//delay(turningTime2);
			}
		}
	}

	else{ //worst case scenario when it doesn't find a line
		left(turningSpeed,turningSpeed); //rotate till death
	}
}
