#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

int turningSpeed=150; //speed that it turns with
int turningTime=2000; //time to turn

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
	//this should be enough for line following
	irScan();
	detectPostion();

	if (!irNothing){//checks for line existance
		if(!(irRight || irLeft || irFull)){
			pidControl();
			setMotors(motorspeeda, motorspeedb);
		}
		//follow right wall 
		else { //intersection or turn
			if(irRight || irFull) {
				right(turningSpeed, turningSpeed);
				delay(turningTime);
			}
			else{ 
				left(turningSpeed, turningSpeed);
				delay(turningTime);
			}
		}
	}
	else{ //worst case scenario when it doesn't find a line
		left(turningSpeed,turningSpeed); //rotate till death
	}
}
