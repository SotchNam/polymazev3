#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

const int turningSpeed = 150; //speed that it turns with
const int turningTime = 1500; //time to turn
const int uTurnTime = 2000;
const int motorspeed1 = 150;
const int motorspeed2 = 150;

char array[999];
int i=0;

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
	irScan();
	detectPostion();

	if(!irEnd){
		if (!irNothing){//checks for line existance
			if(irMid){//no intersections
				pidControl();
				forward(motorspeed1,motorspeed2);
			}

			//follow right wall 
			else { //intersection or turn
				if(irRight || irFull) {
					right(turningSpeed, turningSpeed);
					array[i]= 'r';
					delay(turningTime);
				}
				else{
					left(turningSpeed, turningSpeed);
					array[i]= 'l';
					delay(turningTime);
				}
				i++;
			}
		}

		else{ //worst case scenario when it doesn't find a line
			left(turningSpeed,turningSpeed); //rotate till death
			delay(uTurnTime);
			array[i]='u';
		}
	}
}
