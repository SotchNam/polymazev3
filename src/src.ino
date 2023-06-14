#include "motors.h"

/*ir sensors*/
//needs change
#define SensorCount 8
const int irSensorPins[SensorCount] = {2, 4, 5, 12, 13, 14, 15, 27};
uint16_t sensorValues[SensorCount];
uint16_t position;
uint16_t readsum;

/*other pins*/
#define buzzerPin 99

/*functions declaration*/
void irScan();

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
void irScan(){
	//read analog values
	sensorValues[0]= analogRead(irSensorPins[0]);
	sensorValues[1]= analogRead(irSensorPins[1]);
	sensorValues[2]= analogRead(irSensorPins[2]);
	sensorValues[3]= analogRead(irSensorPins[3]);
	sensorValues[4]= analogRead(irSensorPins[4]);
	sensorValues[5]= analogRead(irSensorPins[5]);
	sensorValues[6]= analogRead(irSensorPins[6]);
	sensorValues[7]= analogRead(irSensorPins[7]);
	//calc position
	position=0;
	readsum=0;
	int i;
	// weighted average
	for(i=0; i< SensorCount; i++){
		position+= i*1000*sensorValues[i];
		readsum+= sensorValues[i];
	}

	position = position/readsum; // between 0 and 8000
	// 0 to the right, 1000 for each sensor 
	// 8000 to the left 
	if (position>=3000 || position <=5000) {
		irFull= false, irRight= false, irLeft= false, irNothing= false, irMid= false, Obstacle= false;

		if(sensorValues[5]<600 && sensorValues[2]<600 && sensorValues[3]>600 && sensorValues[4]>600){
		irMid=true;
		}
		else if (readsum>4000){
		irFull=true;
		}
		else{
		irNothing=true;
		}

	}
	else if (position<3000){
		irFull= false, irRight= false, irLeft= false, irNothing= false, irMid= false, Obstacle= false;
	irRight=true;
	}
	else if (position>5000){
		irFull= false, irRight= false, irLeft= false, irNothing= false, irMid= false, Obstacle= false;
	irLeft=true;
	}
}

void buzzer(){
	tone(buzzerPin, 1000);
	delay(100);
	noTone(buzzerPin);
}
