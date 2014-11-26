#define RIGHT_MOTOR_PORT 2
#define LEFT_MOTOR_PORT 0
#define STANDARD_TURN_SPEED 200

static int unitsPer360Turn = 4700000; //this number of units will makes the robot turn 360 degrees. Calculate with testTurnSpeed().

int main(){
	//printf(VAR+" ");
	turnLeftDeg(180);
	return(0);
}

void setup(){ //deal with initializing everything
	
}

/*
1 dist unit = 1 second at speed 100 with standard wheels;
*/
int testTurnSpeed(){ //account for the distance between the wheels, etc. Returns a "dist" number which represents a 360 degree turn. Speed of turn * length of turn = value returned. 
	//Thus, it takes X number of units (X determined here), to turn 360 degrees.
	int currentPosition = 0;
	int FIRST_SPEED = 250; //speed at which for the first portion.
	int TIMEINTERVAL = 40;
	printf("Please press A when the Robot has turned 90 degrees. \n");
	while(a_button_clicked()==0){ //turn a bit past 90 degrees.
		turnRight(FIRST_SPEED, TIMEINTERVAL);
		currentPosition = currentPosition + (FIRST_SPEED*TIMEINTERVAL);
	}
	
	printf("Moving back a bit. \n");
	int toMoveBack = currentPosition/5; //move back 1/5 of the distance.
	turnLeft(FIRST_SPEED, toMoveBack/FIRST_SPEED);
	
	printf("Please press A when the Robot is back at 90 degrees. \n");
	while(a_button_clicked()==0){ //turn to 90 degrees at 1/4 previous speed.
		turnRight(FIRST_SPEED/4, TIMEINTERVAL);
		currentPosition = currentPosition + (FIRST_SPEED/4*TIMEINTERVAL);
	}
	
	printf("Current Value: %d \n Will now turn 360 degrees. \n", currentPosition*4);
	
	turnRight(500, currentPosition*4/500); //make 360 degree turn at speed 300.
	
	printf("Button A: Done \n Button B: Redo \n");
	int button = getFirstButtonPressed();
	if(button == 0){
		printf("360 degree turn value: %d \n", (currentPosition*4));
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

void turnRight(int speed, int time){
	mav(RIGHT_MOTOR_PORT, speed);
	mav(LEFT_MOTOR_PORT, (speed*-1));
	msleep(time);
	mav(LEFT_MOTOR_PORT, 0);
	mav(RIGHT_MOTOR_PORT, 0);
}

void turnLeft(int speed, int time){
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
	if(unitsPer360Turn == -1){printf("ERROR: Define unitsPer360Turn! \n");}
	else{
		float percentTurn = (float)deg/360;
		turnLeft(STANDARD_TURN_SPEED, (unitsPer360Turn*percentTurn)/STANDARD_TURN_SPEED);//unitsPer360Turn:360 as ? : deg
	}
}

int turnRightDeg(int deg){
		if(unitsPer360Turn == -1){printf("ERROR: Define unitsPer360Turn! \n");}
	else{
		float percentTurn = (float)deg/360;
		turnRight(STANDARD_TURN_SPEED, (unitsPer360Turn*percentTurn)/STANDARD_TURN_SPEED);//unitsPer360Turn:360 as ? : deg
	}
}
