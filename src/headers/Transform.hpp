#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Point.hpp"
#include "Vector.hpp"




class Transform {
private:
  FLOAT mtxFwd[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  FLOAT mtxInv[3][3]= {{1, 0, 0},  {0, 1, 0},  {0, 0, 1}};


  bool doShift = false;
  bool doScale = false;
  bool doRotate = false;

  Point shift;
  FLOAT scaleX = 1, scaleY = 1, scaleZ = 1;
  FLOAT rotateAngle;
  Vector rotateAxis;
  void rotationMatrix();

public:
  Transform();
  void setShift(const Point &p);
  void setScale(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ );
  void setRotate(const Vector &axis, FLOAT angle);

  Vector transform (Vector &v);

  Vector inverseTransform (Vector &v);

  // the two methods below transform in-place
  Point &inverseTransform (Point &p);
  Point &transform (Point &p);

};


#endif
