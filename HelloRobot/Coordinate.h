/*
 * Coordinate.h
 *
 *  Created on: Jul 2, 2015
 *      Author: colman
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

// #include "limits.h"

class Coordinate
{
	public:
	// Constructors.
	Coordinate();
	Coordinate(double x, double y);

	double x;
	double y;

	virtual ~Coordinate();
	bool operator<(const Coordinate& cell) const
	{
		return (y/**INT_MAX*/ + x < cell.y/**INT_MAX*/ + cell.x);
	}
};



#endif /* COORDINATE_H_ */
