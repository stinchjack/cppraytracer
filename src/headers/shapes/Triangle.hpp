
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <utility>
#include "Shape.hpp"

class Triangle: public Shape {

  FLOAT max_l = -1;
  Vector normal;
  Point e1, e2;
public:
  Triangle (Point &p0, Point &p1, Point &p2);


  FLOAT l0 = (p1-p0).length();
  FLOAT l1 = (p2-p1).length();
  FLOAT l2 = (p0-p2).length();
  max_l = max(l0, l1);
  if (l2>max_l) {
    max_l = l2;
  }

  normal =  (p1 - p0).cross(p2-p0);
  e1 = p1 - p0;
  e2 = p2 - p0;
};


#endif
