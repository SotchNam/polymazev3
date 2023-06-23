#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

const int turningSpeed= 130; //speed that it turns with
const int turningOff = 70;
const int turningTime= 1100; //time to turn
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
	forward(turningSpeed,turningSpeed);
	delay(20);
}



void loop() {
	irScan();
	detectPostion();

	//forward(0,0);

	if (!irNothing){//checks for line existance
		if(irMid){//no intersections
			buzzed=0;
			Serial.println("mid:");
			lightLed(Colors(6));
			buzzerCallback();
			pidControl();
			forward(motorspeeda,motorspeedb);
		}

		//follow right wall 
		else if(irRight || irFull) { //intersection or turn
			lightLed(Colors(1));
			Serial.println("right:");
			right(turningSpeed,turningSpeed-turningOff);
			delay(turningTime);
			//forward(turningSpeed,turningSpeed);
			//delay(turningTime2);
			if(!buzzed){
				buzzer();
			}
			buzzed=1;
		}
		else if (irLeft){
			lightLed(Colors(3));
			left(turningSpeed-turningOff, turningSpeed);
			Serial.println("left:");
			delay(turningTime);
			//forward(turningSpeed,turningSpeed);
			//delay(turningTime2);
			if(!buzzed){
				buzzer();
			}
			buzzed=1;
		}
	}
	

	else{ //worst case scenario when it doesn't find a line
		Serial.println("nothing"); 
		lightLed(Colors(0));
		right(turningSpeed,turningSpeed); //rotate till death
	}
}
