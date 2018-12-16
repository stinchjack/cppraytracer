
#ifndef POINT_HPP
#define POINT_HPP

#include <math.h>
#include "Float.hpp"

class Point {

  private:

  public:

    FLOAT x,y,z;
    Point();
    Point (FLOAT x, FLOAT y, FLOAT z);
    Point (const FLOAT &);

    Point& operator+=(const Point &rhs);
    Point operator+(const Point &rhs);

};


#endif
