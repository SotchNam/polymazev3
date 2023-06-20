/*ir sensors*/
//needs change
#define SensorCount 8
const int irSensorPins[SensorCount] = {25, 36, 39, 34, 35, 32, 33, 26};
uint16_t sensorValues[SensorCount];
uint16_t position;
uint16_t readsum;
const int leftbound = 3000;
const int rightbound = 4000;
const int thres = 2000; //threshhold value, max sensor reading is 4095
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
	// value is between 0 and 7000
	// 0 to the right, 1000 for each sensor 
	// 7000 to the left 
}

void detectPostion(){
	//ngl hate this binary logic here
	//pid can use position as error, target is always 4000
	if (position>=leftbound || position <=rightbound) {
		//checks for side sensors if their readings are weak or not
		if(sensorValues[5]<thres && sensorValues[2]<thres && sensorValues[3]>thres && sensorValues[4]>thres){
			irMid=true;
		}
		//checks if most readings are high
		else if (readsum>(thres*9)){
			irFull=true;
		}
		//else the position is mid cuz there's nothing
		//readings wont be 0 when nothing cuz physics, else that'd be a problem 
		else{
			irNothing=true;
		}
	}
	else if (position<leftbound){
		irRight=true;
	}
	else if (position>rightbound){
		irLeft=true;
	}
}
