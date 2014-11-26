#define RIGHT_MOTOR_PORT 2
#define LEFT_MOTOR_PORT 0
#define STANDARD_TURN_SPEED 200
#define PIXELS_TO_DEGREES 1;
#define CAMERA_WIDTH 160;
static int unitsPer360Turn = 4700000; //this number of units will makes the robot turn 360 degrees. Calculate with testTurnSpeed().
static int unitsPerCM = -1;


int main(){
	//printf(VAR+" ");
	testTurnSpeed();
	turnLeftDeg(180, STANDARD_TURN_SPEED);
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
	camera_open();
	camera_update();
}

int goTowardsObject(int channel){
	int allowance = 10; //tweak
	int increment = 10; //tweak
	//do a circle to identify object.
	//turn back and forth in smaller increments until it's in the middle of the image
	//go forwards
	//recurse
	camera_update();
	while(areWeThereYet(channel) == 0){
		AlignWithObject(channel, allowance);
		goStrightInCM(increment);
	}
}

int testPixelsToDegrees(){
	
}

void goStraight(int speed, int dist){ //negatives will go backwards, positives forwards. //dist = speed * time; time = dist/speed
	mav(LEFT_MOTOR_PORT, speed);
	mav(RIGHT_MOTOR_PORT, speed);
	msleep(dist/speed); //check this forumula.
	mav(LEFT_MOTOR_PORT, 0);
	mav(RIGHT_MOTOR_PORT, 0);
}

void AlignWithObject(int channel, int allowance){ //recursive implementation (?) of binary search with closerToAlignedWithObject(). Allowance is the required accuracy. 3 will get it to within 3 pixels.
	//int marginOfError = 64;
	while(abs(offsetFromObject(channel, 0)) > allowance){
		moveTowardAlignedWithObject(channel, 0.9);
	}
}

void moveTowardAlignedWithObject(int channel, float turnMultiplier, int speed){ //with turnMultiplier set to 0.75, if it expects to need to turn 10 degrees, it will turn 7.5 degrees toward the object.
	turnDeg((offsetFromObject(channel, 0)*PIXELS_TO_DEGREES*turnMultiplier), speed); //check for bugs with float multiplication.
	//turn to be aligned.
}


int offsetFromObject(int channel, int index){ //positive = Object to right; negative = Object to left; returns the distance from the center of the camera to the center of the object.
	point2 objectCenter = get_object_center(channel, 0);
	int output = -1*(CAMERA_WIDTH-(objectCenter.x)));
	return output;
}

void driveStraightWithTracking(int dist){
	
}

int goStrightInCM(int cm){
	
}

void turnDeg(int deg, int speed){ //clockWise amount
	if(deg > 0){
		turnRight(deg, speed);
	} else if(deg < 0){
		turnLeft(deg, speed);
	}
}

int turnLeftDeg(int deg, int speed){ //perform a turn of deg degrees.
	if(unitsPer360Turn == -1){printf("ERROR: Define unitsPer360Turn! \n");}
	else{
		float percentTurn = (float)deg/360;
		turnLeft(speed, (unitsPer360Turn*percentTurn)/speed);//unitsPer360Turn:360 as ? : deg
	}
}

int turnRightDeg(int deg, int speed){
	if(unitsPer360Turn == -1){printf("ERROR: Define unitsPer360Turn! \n");}
	else{
		float percentTurn = (float)deg/360;
		turnRight(speed, (unitsPer360Turn*percentTurn)/speed);//unitsPer360Turn:360 as ? : deg
	}
}
