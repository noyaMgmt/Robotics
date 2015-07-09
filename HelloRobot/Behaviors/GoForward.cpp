/*
 * GoForward.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: user
 */

#include "GoForward.h"
#include <iostream>
#include <math.h>
#include "../config.h"

bool GoForward::startCond()
{
	return (_robot->isForwardFree());
}

bool GoForward::stopCond()
{
	return (!_robot->isForwardFree());
}

void GoForward::action()
{
	_robot->setSpeed(MOVE_SPEED, 0.0);
}

void GoForward::SetNewYaw(double yaw)
{
	//nothing
}

GoForward::GoForward(Robot* robot, double num):Behavior(robot) {
	_robot = robot;
}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}
