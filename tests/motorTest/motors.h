/*motors*/
//needs change
#define motor1      13   // right wheel
#define motor2      15   // left wheel
#define motor1Speed 12	 // right wheel speed 
#define motor2Speed 4	 // left wheel speed


void forward(int speed1, int speed2){
	digitalWrite(motor1,1);
	digitalWrite(motor2,1);
	analogWrite(motor1Speed,speed1);
	analogWrite(motor2Speed,speed2);
}

void back(int speed1,int speed2){
	digitalWrite(motor1,0);
	digitalWrite(motor2,0);
	analogWrite(motor1Speed,speed1);
	analogWrite(motor2Speed,speed2);
}

void right(int speed1,int speed2){
	digitalWrite(motor1,0);
	digitalWrite(motor2,1);
	analogWrite(motor1Speed,speed1);
	analogWrite(motor2Speed,speed2);
}

void left(int speed1,int speed2){
	digitalWrite(motor1,1);
	digitalWrite(motor2,0);
	analogWrite(motor1Speed,speed1);
	analogWrite(motor2Speed,speed2);
}

void setMotors(int speed1, int speed2){
	if (speed1 > 0) digitalWrite(motor1,1);
	else digitalWrite(motor1,0);
	analogWrite(motor1Speed,abs(speed1));

	if (speed2 > 0) digitalWrite(motor2,1);
	else digitalWrite(motor2,0);
	analogWrite(motor2Speed,abs(speed2));
}
