/*
 * WayPoint.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */


#include "WayPoint.h"

WayPoint::WayPoint(double x, double y, double rotateAngle)
{
	this->coordinate.x = x;
	this->coordinate.y = y;
	this->rotate = rotateAngle;
}

WayPoint::WayPoint()
{
	this->coordinate.x = 0;
	this->coordinate.y = 0;
	this->rotate = 0;
}

WayPoint::~WayPoint() {}
