/*
 * WayPointsManager.h
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <iostream>
#include <vector>
#include "WayPoint.h"
#include "Coordinate.h"
#include <math.h>
using std::vector;

class WayPointsManager
{
	public:

		// Members.
		vector<WayPoint> wayPoints; // All the WayPoints coordinates.
		int numOfWayPoints; // The count of all the WayPoints coordinates.

		// Methods.
		WayPointsManager(vector<Coordinate> path);
		void buildWayPoints();

	private:

		// Members.
		vector<Coordinate> aStarPath;

		// Methods.
		double calculateRotate(int i);
		bool isSameDirection (int i);
		int getAngle (int x, int y);
};



#endif /* WAYPOINTSMANAGER_H_ */
