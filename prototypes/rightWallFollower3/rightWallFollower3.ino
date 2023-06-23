#include "motors.h"
#include "qtr.h"
#include "tcs.h"
#include "buzzer.h"
#include "pid.h"

//task to detect the colors
void task(void *parameter){
	//tcs setup
	gammaSetup();
	ledSetup();
	while(1){
		detectColor();
		lightLed();
	}
}

const int turningSpeed= 190; //speed that it turns with
const int turningOff = 70;
const int turningTime= 600; //time to turn
const int turningTime2= 600;
const int stopTime =000;
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
	//buzzer setup
	pinMode(buzzerPin, OUTPUT);
	//indicate the beginning of the end
	buzzer();
	forward(0,0);
	//delay(20);
	
	//color tread activate
  xTaskCreatePinnedToCore(task, "colorView", 10000, NULL, 1, NULL, 0);
}



void loop() {
	irScan();
	detectPostion();


	if (!irNothing){//checks for line existance
		if(irMid){//no intersections
			pidControl();
			forward(motorspeeda,motorspeedb);
			buzzed=0;
			buzzerCallback();
		}

		//follow right wall 
		else if(irRight || irFull) { //intersection or turn
			left(0, 0);
			delay(stopTime);
			right(turningSpeed-turningOff,turningSpeed);
			delay(turningTime);
			do{
			right(turningSpeed-turningOff,turningSpeed);
			irScan();
			detectPostion();
			} while (frontReading && irMid);
			forward(turningSpeed,turningSpeed);
			delay(turningTime2);
			if(!buzzed){
				buzzer();
			}
			buzzed=1;
		}
		
		else if(frontReading){
			irScan();
			detectPostion();
			//delay(turningTime2);
		}

		else if (irLeft){
			right(0,0);
			delay(stopTime);
			left(turningSpeed, turningSpeed-turningOff);
			delay(turningTime);
			do{
			left(turningSpeed, turningSpeed-turningOff);
			irScan();
			detectPostion();
			delay(turningTime);
			} while (frontReading && irMid);
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
		do{right(turningSpeed- turningOff,turningSpeed-turningOff);} //rotate till death
		while(frontReading );
	}
}
