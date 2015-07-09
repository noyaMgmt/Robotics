/*
 * Plan.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLAN_H_
#define PLAN_H_

#include "../config.h"
#include "../Robot.h"
#include "../Behaviors/GoForward.h"
#include "../Behaviors/TurnLeft.h"
#include "../Behaviors/TurnRight.h"

class Plan {

protected:
	Robot* _robot;
	Behavior* _start;
	Behavior** _behaviors;

public:
	Plan(Robot* robot);
	virtual Behavior* getStartPoint();
	virtual ~Plan();
};

#endif /* PLAN_H_ */
