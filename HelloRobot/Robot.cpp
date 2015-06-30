
#include "Robot.h"
#include <math.h>

Robot::Robot(char* ip, int port) {

	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);


	_pp->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
        
     //TODO set start position
    XPos = 0;
	YPos = 0;
	Yaw = 0;
        _pp->SetOdometry(XPos,YPos,Yaw);
}

void Robot::Read()
{
	_pc->Read();
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

double Robot::getXpos() {
	return _pp->GetXPos();
}

double Robot::getYpos() {
	return _pp->GetYPos();
}

// return in degr
double Robot::getYaw() {
	return ((_pp->GetYaw())*180/M_PI);
}

LaserProxy* Robot::getLaser()
{
	return (_lp);
}


float Robot::getLaserDistance(int index)
{
    return _lp->GetRange(index);
}

bool Robot::checkRange(int nStart, int nEnd)
{
    bool rangeClear = true;

    for (int index = nStart; (index <= nEnd) && (rangeClear); index++)
    {
    	rangeClear = (this->getLaserDistance(index) > DISTANCE_TOLERANCE);
    }

    return (rangeClear);
}
int Robot::deg_to_index(double deg)
{
	return (deg + 120) / 0.36;
}


double Robot::getLaserSpec()
{
	return(((_lp->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
}


bool Robot::isRightFree() {
    // TODO consts
    return this->checkRange(0,100)
}

bool Robot::isLeftFree() {
    // TODO consts
    return this->checkRange(566,666)
}

bool Robot::isForwardFree() {
    // TODO consts
    return this->checkRange(150,450)
}


Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
