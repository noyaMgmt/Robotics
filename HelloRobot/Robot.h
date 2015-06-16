/*
 * Robot.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient _pc;
	Position2dProxy _pp;
	LaserProxy _lp;
	float _lastX, _lastY, _lastYaw;

public:
	Robot(string ip, int port);
	virtual ~Robot();

	void setSpeed(float linear, float angular);
	float getX();
	float getY();
	float getYaw();

	float* getLaserScan();
	int deg_to_index(double deg);
};

#endif /* ROBOT_H_ */
