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
     

  bool doShift = false;
  bool doScale = false;
  bool doRotate = false;
    
  Point shift;
  FLOAT scale;
  FLOAT rotateAngle;
  Vector rotateAxis;
     
public:
  void setShift(Point &p);
  void setScale(FLOAT scale);
  void setRotate(Vector &axis, FLOAT angle);
  
  Point transform (Point &p);
  Vector transform (Vector &v);
  Point inverseTransform (Point &p);
  Vector inverseTransform (Vector &v);     
  
};

#endif
