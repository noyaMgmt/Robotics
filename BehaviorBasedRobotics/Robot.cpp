/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
	// TODO Auto-generated constructor stub
	_lastX = _pp.GetXPos();
	_lastY = _pp.GetYPos();
	_lastYaw = _pp.GetYaw();
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

void Robot::setSpeed(float linear, float angular)
{
	_pp.SetSpeed(linear, angular);
}

float Robot::getX()
{
	return _pp.GetXPos();
}

float Robot::getY()
{
	return _pp.GetYPos();
}

float Robot::getYaw()
{
	return _pp.GetYaw();
}

float* Robot::getLaserScan()
{
	float *scan = new float[_lp.GetCount()];
	for (unsigned int i = 0; i < _lp.GetCount(); i++)
	{
		scan[i] = _lp[i];
	}
	return scan;
}

int Robot::deg_to_index(double deg)
{
	return (deg + 120) / 0.36;
}
