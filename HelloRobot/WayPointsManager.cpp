/*
 * WayPointsManager.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */


#include "WayPointsManager.h"
#include <math.h>

using namespace std;

WayPointsManager::WayPointsManager(vector<Coordinate> aStarPath)
{
	this->aStarPath = aStarPath;
	this->wayPoints.reserve(aStarPath.size());
	this->numOfWayPoints = 0;
}

void WayPointsManager::buildWayPoints()
{

	// Defines the start point as a WayPoint.
	this->wayPoints[0].coordinate = this->aStarPath[0];
	this->numOfWayPoints++;

	// TODO Check if we need to rotate the robot by checking the direction of the second point.
	//this->wayPoints[0].rotate = //something.

	int i;

	// Running from the third point to the last point to define all the
	// WayPoints whenever the robot need to rotate to change direction.
	for (i = 2; i < this->aStarPath.size(); i++)
	{
		// Checking whether the current point is in the same direction as
		// the last two points.
		if (!this->isSameDirection(i))
		{
			// The robot is not in the same direction.
			// Adding the current point to the WayPoints.
			this->wayPoints[this->numOfWayPoints].coordinate = this->aStarPath[i];

			// Setting the rotation the robot need to do on this WayPoint.
			this->wayPoints[this->numOfWayPoints].rotate = this->calculateRotate(i);

			// Counting how many WayPoints we have so far.
			this->numOfWayPoints++;
		}
	}
}

bool WayPointsManager::isSameDirection(int i)
{
	// Getting the current point and the last two points of the robot.
	Coordinate current = this->aStarPath[i];
	Coordinate previous = this->aStarPath[i-1];
	Coordinate last = this->aStarPath[i-2];

	// If the sub of the current and the previous coordinates is equals
	// to the sub of the previous and the last coordinates, it means that the
	// robot is still in the same direction.
	if ((current.x - previous.x == previous.x - last.x) &&
		(current.y - previous.y == previous.y - last.y))
	{
		return (true);
	}
	else
	{
		return (false);
	}

}

double WayPointsManager::calculateRotate(int i)
{
	// Getting the current point and the last two points of the robot.
	Coordinate current = this->aStarPath[i];
	Coordinate previous = this->aStarPath[i-1];
	Coordinate last = this->aStarPath[i-2];

	// Subs the coordinates to calculate the right rotation.
	Coordinate lastDirection;
	Coordinate currentDirection;

	lastDirection.x = previous.x - last.x;
	lastDirection.y = previous.y - last.y;
	currentDirection.x = current.x - previous.x;
	currentDirection.y = current.y - previous.y;

	// Getting the angle that the robot was when it moved from the last point to the previous point.
	int lastAngle = this->getAngle(lastDirection.x, lastDirection.y);

	// Getting the angle that the robot should be when it moves from the previous point to the current point.
	int currentAngle = this->getAngle(currentDirection.x, currentDirection.y);

	// Calculates the right angle the robot should rotate.
	int correctAngle = lastAngle - currentAngle;

	// If the result of the correct angle is below 0, we need to add to
	// the result 360, so the result will be in the range of a full round (0-360).
	if (correctAngle < 0)
	{
		correctAngle = 360 + correctAngle;
	}

	// Returns the right angle the robot should rotate.
	return (correctAngle);
}

// Getting the sub of two coordinates, x and y,
// and calculates the angle the robot should face on the matrix,
// if we treat the matrix as a number line (x,y).
int WayPointsManager::getAngle(int x, int y)
{
	if (x == 1)
	{
		switch (y)
		{
			// Robot moved down-right. Means the angle is 315.
			case (1):
			{
				return (315);
				break;
			}
			// Robot moved down. Means the angle is 270.
			case (0):
			{
				return (270);
				break;
			}
			// Robot moved down-left. Means the angle is 225.
			case (-1):
			{
				return (225);
				break;
			}
			// Not an optional option. But to return some statement,
			// returns 0, so the robot won't change an angle.
			default: return (0);
		}
	}
	else if (x == 0)
	{
		switch (y)
		{
			// Robot moved right. Means the angle is 360 (or 0).
			case (1):
			{
				return (360);
				break;
			}
			// Robot moved left. Means the angle is 180.
			case (-1):
			{
				return (180);
				break;
			}
			// Not an optional option. But to return some statement,
			// returns 0, so the robot won't change an angle.
			default: return (0);
		}
	}
	else if (x == -1)
	{
		switch (y)
		{
			// Robot moved up-right. Means the angle is 45.
			case (1):
			{
				return (45);
				break;
			}
			// Robot moved up. Means the angle is 90.
			case (0):
			{
				return (90);
				break;
			}
			// Robot moved up-left. Means the angle is 135.
			case (-1):
			{
				return (135);
				break;
			}
			// Not an optional option. But to return some statement,
			// returns 0, so the robot won't change an angle.
			default: return (0);
		}
	}

	// Not an optional option. But to return some statement,
	// returns 0, so the robot won't change an angle.
	return 0;
}
/*
bool WayointsManager::isInWayPoint(double x,double y)
{
	double dx = nextWayPoint.x_Coordinate - x;
	double dy = nextWayPoint.y_Coordinate - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	cout << "way point x"<< " " << nextWayPoint.x_Coordinate << " " << "x" << " " << x << endl;
	cout << "way point y" << " " << nextWayPoint.y_Coordinate << " " << "y" << " "  << y << endl;
	cout << "yaw" << nextWayPoint.yaw <<  endl;
	cout << (distance) << endl;

	// TODO
	/*if (distance*_gridResolution <= TOLLERANCE)
	{
		return true;
	}
	return false;
}*/

