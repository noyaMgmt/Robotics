/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"


Manager::Manager(Robot* robot, Plan* pln, localizationManager* l_manager, ConfigurationManager* cm, WayPointsManager* wayPointsManager) {
	_robot = robot;
	_wayPointsManager = wayPointsManager;
	_curr = pln->getStartPoint();

	_localization_manager = new localizationManager(robot);
	_cm = cm;
}
void Manager::run()
{
	WayPoint wpm;
	set<WayPoint>::iterator it;
	
	_robot->Read();

	// Gets the position of the robot
	double x_Coordinate = _robot->getXpos();
	double y_Coordinate = _robot->getYpos();
	double dYaw = _robot->getYaw();

	bool behavior_exsist = true;
	
	for (it = (_wayPointsManager->wayPoints).begin(); it != (_wayPointsManager->wayPoints).end(); ++it) {
		wpm = *it;
		_robot->Read();

		_wayPointsManager->setNextWayPoint(wpm);

		while (_curr != NULL){
			
			// If the current behavior can't run
			if(_curr->stopCond())
			{
				// Perform the next behavior according to the plan
			    _curr = _curr->selectNextBehavior();

			    _robot->Read();
			}
			
			if (_wayPointsManager->isInWayPoint(_robot->getXpos(),_robot->getYpos()))
			{
				// handel way point
				// get the new yaw we need to turn
				_curr.SetNewYaw(_robot->getYaw() + it.rotate);
				// set behavir to turn left
				_curr = _curr->selectNextBehavior();
			}

			_curr->action();

			_robot->Read();			

			// Gets the position of the robot after read
			double current_x_coordinate = _robot->getXpos();
			double current_y_coordinate = _robot->getYpos();
			double current_yaw = _robot->getYaw();

			double deltaX = current_x_coordinate - x_Coordinate;
			double deltaY = current_y_coordinate - y_Coordinate;
			double deltaYaw = current_yaw - dYaw;

			_localization_manager->update(deltaX, deltaY, deltaYaw);

			x_Coordinate = current_x_coordinate;
			y_Coordinate = current_y_coordinate;
			dYaw = current_yaw;
		}
	}
}


Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
