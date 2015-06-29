/*
 * Point.h
 */


#ifndef _POINT_H
#define _POINT_H

#include <string>
using namespace std;

struct Point
{
  Point();
  Point(double px, double py);

  string tostring()                   const;
  double x;
  double y;
};

bool operator == (const Point& lhs, const Point& rhs);
bool operator != (const Point& lhs, const Point& rhs);
bool operator  < (const Point& lhs, const Point& rhs);
bool operator  > (const Point& lhs, const Point& rhs);
bool operator <= (const Point& lhs, const Point& rhs);
bool operator >= (const Point& lhs, const Point& rhs);


ostream& operator << (ostream& os, const Point& p);

#endif
