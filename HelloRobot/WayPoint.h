/*
 * WayPoint.h
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "Coordinate.h"

class WayPoint
{
	public:
		// Members.
		Coordinate coordinate; // The coordinate of the WayPoint.
		double rotate; // Defines how much we need to rotate the robot at this point.

		// Constructors.
		WayPoint();
		WayPoint(double x, double y, double rotateAngle);

		virtual ~WayPoint();

		bool operator<(const Coordinate& cell) const
		{
			return (coordinate.y/**INT_MAX*/ + coordinate.x < cell.y/**INT_MAX*/ + cell.x);
		}
};




#endif /* WAYPOINT_H_ */
