#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "Float.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Transform {
private:
  FLOAT mtxFwd[3][3] =
    {{1, 0, 0},
    {{0, 1, 0},
     {0, 0, 1}};
     
  FLOAT mtxInv[3][3]=
    {{1, 0, 0},
    {{0, 1, 0},
     {0, 0, 1}};
     

  bool shift = false;
  bool scale = false;
  bool rotate = false;

public:
  void setShift(Point &p);
  void setScale(FLOAT scale);
  void setRotate(Vector &axis, FLOAT angle);
  
  void transform (Point &p);
  void transform (Vector &v);
  
};

#endif
