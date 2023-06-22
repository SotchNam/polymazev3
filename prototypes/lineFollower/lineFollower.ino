#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"

int motorspeed1 = 150;
int motorspeed2 = 150;

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
	if (irMid){
		forward(motorspeed1,motorspeed2);
	}else{
		if (irFull || irRight){
			buzzer();
			right(motorspeed1,motorspeed2);
		}else{
			if (irLeft){
				left(motorspeed1,motorspeed2);
				buzzer();
			}else{
				if(irNothing){
					left(motorspeed1,motorspeed2);
					buzzer();
				}		
			}		
		}
	}
}
