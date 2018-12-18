
#ifndef POINT_HPP
#define POINT_HPP

#include <math.h>
#include "Float.hpp"
class Vector;

class Point {
  friend class Vector;

  private:


  public:

    FLOAT x,y,z;
    Point();
    Point (FLOAT x, FLOAT y, FLOAT z);
    Point (const FLOAT &);

    Point& operator+=(const Point &rhs);
    Point operator+(const Point &rhs);
    FLOAT operator*(Point &rhs);
    FLOAT operator*(Vector &rhs);

};


#endif
