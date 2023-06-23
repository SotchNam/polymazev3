#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

const int turningSpeed= 150; //speed that it turns with
const int turningOff = 30;
const int turningTime= 1200; //time to turn
const int turningTime2= 200;
bool buzzed =0;

void setup() {
	//Serial.begin(9600);

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
	forward(0,0);
	//delay(20);
}



void loop() {
	irScan();
	detectPostion();


	if (!irNothing){//checks for line existance
		lightLed(Colors(6));
		if(irMid){//no intersections
			pidControl();
			forward(motorspeeda,motorspeedb);
			buzzed=0;
			//Serial.println("mid:");
			buzzerCallback();
		}

		//follow right wall 
		else if(irRight || irFull) { //intersection or turn
			left(turningSpeed, turningSpeed-turningOff);
			Serial.println("right:");
			delay(turningTime);
			forward(turningSpeed,turningSpeed);
			delay(turningTime2);
			if(!buzzed){
				buzzer();
			}
			buzzed=1;
		}
		else if (irLeft){
			right(turningSpeed-turningOff,turningSpeed);
			Serial.println("left:");
			delay(turningTime);
			forward(turningSpeed,turningSpeed);
			delay(turningTime2);
			if(!buzzed){
				buzzer();
			}
			buzzed=1;
		}
	}
	

	else{ //worst case scenario when it doesn't find a line
		Serial.println("nothing"); 
		lightLed(Colors(0));
		right(200,200); //rotate till death
	}
}
