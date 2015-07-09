
#include "TurnLeft.h"

bool TurnLeft::startCond(){
	return (true);
}

bool TurnLeft::stopCond(){
	diff = _robot->getYaw()-_yaw
	if diff < 0
		diff = abs(diff +360);
	else if diff > 360
		diff = abs(diff - 360);
	return ( diff <= MAX_YAW_DIFF );
}

void TurnLeft::action(){
	_robot->setSpeed(0.0, TURN_LEFT_SPEED);
}

TurnLeft::TurnLeft(Robot* robot, double newYaw):Behavior(robot) {
	// TODO Auto-generated constructor stub
	_yaw = newYaw;
}

void GoForward::SetNewYaw(double yaw)
{
	_yaw =yaw;
}

TurnLeft::~TurnLeft() {
	// TODO Auto-generated destructor stub
}

