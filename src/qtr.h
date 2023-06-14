/*ir sensors*/
//needs change
#define SensorCount 8
const int irSensorPins[SensorCount] = {2, 4, 5, 12, 13, 14, 15, 27};
uint16_t sensorValues[SensorCount];
uint16_t position;
uint16_t readsum;
bool irFull = false;
bool irRight = false;
bool irLeft = false;
bool irNothing = false;
bool irMid = false;

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

	//resets vars
	position=0;
	readsum=0;
	irFull= false, irRight= false, irLeft= false, irNothing= false, irMid= false;
	int i;

	// calculating weighted average
	for(i=0; i< SensorCount; i++){
		position+= i*1000*sensorValues[i];
		readsum+= sensorValues[i];
	}

	if( readsum>0) {position = position/readsum;} 
	// value is between 0 and 8000
	// 0 to the right, 1000 for each sensor 
	// 8000 to the left 

	//ngl hate this binary logic here
	//pid can use position as error, target is always 4000
	///*
	if (position>=3000 || position <=5000) {
		//checks for side sensors if their readings are weak or not
		if(sensorValues[5]<600 && sensorValues[2]<600 && sensorValues[3]>600 && sensorValues[4]>600){
		irMid=true;
		}
		//checks if most readings are high
		else if (readsum>4000){
		irFull=true;
		}
		//else the position is mid cuz there's nothing
		//readings wont be 0 when nothing cuz physics, else that'd be a problem 
		else{
		irNothing=true;
		}
	}
	else if (position<3000){
	irRight=true;
	}
	else if (position>5000){
	irLeft=true;
	}
	//*/
}
