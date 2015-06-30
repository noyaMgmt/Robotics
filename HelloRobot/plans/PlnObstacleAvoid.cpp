/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"
#include "../behaviors/GoToWayPoint.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) : Plan(robot){

	//Creating Behaviors
	_behaviors = new Behavior*[3];
	_behaviors[0] = new GoForward(robot);
	_behaviors[1] = new TurnLeft(robot);
        _behaviors[2] = new TurnRight(robot);

	//Connecting behaviors
	_behaviors[0]->addNextBehavior(_behaviors[1]);
        _behaviors[0]->addNextBehavior(_behaviors[2]);
	_behaviors[1]->addNextBehavior(_behaviors[0]);
	_behaviors[2]->addNextBehavior(_behaviors[0]);

	_start = _behaviors[0];
}

Behavior* PlnObstacleAvoid::getStartPoint(){
	return _start;
}

PlnObstacleAvoid::~PlnObstacleAvoid() {

	for(int i = 0; i < BEHAVIORS_COUNT; i++)
		delete _behaviors[i];
}
