
#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "config.h"
#define DISTANCE_TOLERANCE 0.5

using namespace PlayerCc;
class Robot {

	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;

public:

	double XPos;
	double YPos;
	double Yaw;
	int _grid_rows;

	Robot(char* ip, int port);
	void Read();
	void setSpeed(float xSpeed, float angularSpeed);
    double getXpos();
	double getYpos();
	double getYaw();
    LaserProxy* getLaser();
    float getLaserDistance(int index);
	bool isRightFree();
	bool isLeftFree();
	bool isForwardFree();
	bool checkRange(int nStart, int nEnd);
	double getLaserSpec();
	int deg_to_index(double deg);

	
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
