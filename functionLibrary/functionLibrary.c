#define RIGHT_MOTOR_PORT 0
#define LEFT_MOTOR_PORT 2


int main(){
	//printf(VAR+" ");
	testTurnSpeed();
	return(0);
}

void setup(){ //deal with initializing everything
	
}

/*
1 dist unit = 1 second at speed 100 with standard wheels;
*/
int testTurnSpeed(){ //account for the distance between the wheels, etc. Returns a "dist" number which represents a 360 degree turn. Speed of turn * length of turn = value returned. 
	int currentPosition = 0;
	int SPEED = 250;
	int TIMEINTERVAL = 40;
	printf("Please press A when the Robot has turned 90 degrees. \n");
	while(a_button_clicked()==0){ //turn a bit past 90 degrees.
		turnRight(SPEED, TIMEINTERVAL);
		currentPosition = currentPosition + (SPEED*TIMEINTERVAL);
	}
	
	printf("Moving back a bit. \n");
	int toMoveBack = currentPosition/5; //move back 1/5 of the distance.
	turnLeft(SPEED, toMoveBack/SPEED);
	
	printf("Please press A when the Robot is back at 90 degrees. \n");
	while(a_button_clicked()==0){ //turn to 90 degrees at 1/4 previous speed.
		turnRight(SPEED/4, TIMEINTERVAL);
		currentPosition = currentPosition + (SPEED/4*TIMEINTERVAL);
	}
	
	printf("Current Value: %d \n Will now turn 360 degrees. \n", currentPosition*4);
	
	turnRight(500, currentPosition*4/500); //make 360 degree turn at speed 300.
	
	printf("Button A: Done \n Button B: Redo \n");
	int button = getFirstButtonPressed();
	if(button == 0){
		printf("360 degree turn value: %d \n", currentPosition*4);
	} else if(button == 1){
		return testTurnSpeed();
	} else return -1;
	
}

int getFirstButtonPressed(){ //returns 0 for A, 1 for B, 2 for C.
	while(1==1){
		if(a_button_clicked()==1){
			return 0;
		}
		if(b_button_clicked()==1){
			return 1;
		}
		if(c_button_clicked()==1){
			return 2;
		}
		msleep(40);
	}
}

int turnRight(int speed, int time){
	mav(RIGHT_MOTOR_PORT, speed);
	mav(LEFT_MOTOR_PORT, (speed*-1));
	msleep(time);
	mav(LEFT_MOTOR_PORT, 0);
	mav(RIGHT_MOTOR_PORT, 0);
}

int turnLeft(int speed, int time){
	mav(LEFT_MOTOR_PORT, speed);
	mav(RIGHT_MOTOR_PORT, (speed*-1));
	msleep(time);
	mav(RIGHT_MOTOR_PORT, 0);
	mav(LEFT_MOTOR_PORT, 0);
}

int findValidObject(){ //find an object for the purpose of tracking. Should not move.
	
}

void driveStraightWithTracking(int dist){
	
}

int moveInCM(int cm){
	
}

int turnLeftDeg(int deg){ //perform a turn of deg degrees.
	
}

int turnRightDeg(int deg){
	
}
