/*
 * Coordinate.cpp
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */

#include "Coordinate.h"


Coordinate::Coordinate(double x, double y)
{
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate()
{
	this->x = 0;
	this->y = 0;
}

Coordinate::~Coordinate() {}

