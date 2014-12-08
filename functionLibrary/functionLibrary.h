// Created on Thu December 4 2014

// Replace FILE with your file's name
#ifndef _functionLibrary_H_
#define _functionLibrary_H_

void turnLeft(int speed, int time);
void turnRight(int speed, int time);
void goStraight(int speed, int time);
void goStarightInCM(int cm, int speed);
void setup();
int testTurnSpeed();
int getFirstButtonPressed();
int testDistPerCM(int testDistanceCM);
void turnRight(int speed, int time);
void turnLeft(int speed, int time);
void goStraight(int speed, int time);
int goStraightInCM(int cm, int speed);
void turnDeg(int deg, int speed);
int alignWithWall(int distanceFromWall, int futureDistanceFromWall);
int alignWithCorner(int distanceX, int distanceY, int futuredistanceX, int futuredistanceY, int direction);
int lineFollow(int lineColor, int time);
void servoMoveInDegrees(int servoPort, int degrees);
int calibrateServo(int servoPort, int servoPosition);
#endif
