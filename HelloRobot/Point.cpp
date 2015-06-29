/*
 * Point.cpp
 */

#include "Point.h"
#include <cmath>
#include <sstream>

Point::Point(double px, double py)
  : x(px), y(py)
{}

Point::Point()
  : x(0), y(0)
{}


bool operator == (const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const Point& lhs, const Point& rhs)
{
    return ! (lhs == rhs);
}

bool operator  < (const Point& lhs, const Point& rhs)
{
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator  > (const Point& lhs, const Point& rhs)
{
    return rhs < lhs;
}

bool operator <= (const Point& lhs, const Point& rhs)
{
    return ! (lhs > rhs);
}

bool operator >= (const Point& lhs, const Point& rhs)
{
    return ! (lhs < rhs);
}


string Point::tostring() const
{
    ostringstream out;
    out << "(" << x << ", " << y << ")";
    return out.str();
}

ostream& operator << (ostream& os, const Point& p)
{
    os << p.tostring();
    return os;
}
